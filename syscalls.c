#include "ipc.h"
#include "sched.h"
#include "kprint.h"
#include "system.h"
#include "syscalls.h"

typedef enum {
    EXIT_SYSCALL = 0,
    YIELD_SYSCALL,
    IPC_SEND_ASYNC_SYSCALL,
    IPC_RECV_ASYNC_SYSCALL
} SyscallCode;

bool syscalls_initialized = false;

rvu_word (*syscall_table[32]) (RiscvGPRS *, rvu_word);
rvu_word syscall_yield(RiscvGPRS* regs, rvu_word sepc) {
    // TODO: call into scheduler
    // t0 = syscall number (1)
    sys_kassert(syscalls_initialized == true);
    kprintf(K_DEBUG,
            "syscall [yield]: thread %d yielded core %d\n",
            current_thread->thread_id, sys_core_id());
    sched_enqueue(current_thread);
    // ensures that a new thread from queue is scheduled
    schedule(regs, sepc+4);
    return 0;
}

rvu_word syscall_exit(RiscvGPRS* regs, rvu_word sepc) {
    // t0 = syscall number (0)
    // a0 = exit code
    sys_kassert(syscalls_initialized == true);
    sys_kassert(current_thread != 0);
    kprintf(K_DEBUG,
            "syscall [exit]: thread %d exited with code %d on core %d\n",
            current_thread->thread_id, regs->x10_a0, sys_core_id());
    current_thread->flagged_delete = true;
    sched_run_rr_scheduler(regs, sepc);
    return 0;
}

rvu_word syscall_ipc_send_async(RiscvGPRS* regs, rvu_word sepc) {
    sys_kassert(syscalls_initialized == true);
    sys_kassert(current_thread != 0);
    regs->x10_a0 = ipc_send_async_msg(regs, sepc+4);
    return sepc+4;
}

rvu_word syscall_ipc_recv_async(RiscvGPRS* regs, uint32_t sepc) {
    sys_kassert(syscalls_initialized == true);
    sys_kassert(current_thread != 0);
    regs->x10_a0 = ipc_async_recv_msg(regs, sepc+4);
    return sepc+4;
}

void syscall_setup_table() {
    syscall_table[EXIT_SYSCALL] = syscall_exit;
    syscall_table[YIELD_SYSCALL] = syscall_yield;
    syscall_table[IPC_SEND_ASYNC_SYSCALL] = syscall_ipc_send_async;
    syscall_table[IPC_RECV_ASYNC_SYSCALL] = syscall_ipc_recv_async;
    syscalls_initialized = true;
}

void syscall_validate_code(SyscallCode code) {
    if (code < 0 || code > IPC_RECV_ASYNC_SYSCALL) {
        kprintf(K_DEBUG,
                "syscall: invalid code %d\n", code);
        sys_panic("invalid syscall error");
    }
}

rvu_word syscall_execute(RiscvGPRS* regs, rvu_word sepc) {
    syscall_validate_code(regs->x5_t0);
    rvu_word new_sepc = syscall_table[regs->x5_t0](regs, sepc);
    return new_sepc;
}

int32_t sys_do_yield() {
    uint32_t sys_call_code = YIELD_SYSCALL;
    __asm__("mv t0, %0"
    : /* no output */
    : "r" (sys_call_code)
    : "%t0"
    );
    sys_ebreak();
    return 0;
}

int32_t sys_do_exit(uint32_t code) {
    uint32_t sys_call_code = EXIT_SYSCALL;
    __asm__("mv t0, %0;"
            "mv a0, %1;"
    : /* no output */
    : "r" (sys_call_code), "r" (code)
    : "t0", "a0"
    );
    sys_ebreak();
    return 0;
}

int32_t sys_do_ipc_send_async(struct ipc_msg* msg) {
    uint32_t sys_call_code = IPC_SEND_ASYNC_SYSCALL;
    __asm__("mv t0, %0;"
            "mv a0, %1;"
    : /* no output */
    : "r" (sys_call_code), "r" (msg)
    : "t0", "a0"
    );
    sys_ebreak();
    // return code will be in a0
    int32_t ret_code = 0;
    __asm__("mv t0, %0;"
            "sw a0, 0(t0);"
            : /* no output */
            : "r" (&ret_code)
            : "t0", "a0"
    );
    return ret_code;
}

int32_t sys_do_ipc_recv_async(struct ipc_msg* msg_out) {
    uint32_t sys_call_code = IPC_RECV_ASYNC_SYSCALL;
    __asm__("mv t0, %0;"
            "mv a0, %1;"
    : /* no output */
    : "r" (sys_call_code), "r" (msg_out)
    : "t0", "a0"
    );
    sys_ebreak();
    int32_t ret_code = 0;
    __asm__("mv t0, %0;"
            "sw a0, 0(t0);"
    : /* no output */
    : "r" (&ret_code)
    : "t0", "a0"
    );
    return ret_code;
}