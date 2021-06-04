#include "csr.h"
#include "sched.h"
#include "kprint.h"
#include "system.h"
#include "time.h"
#include "syscalls.h"
#include "constants.h"
#include "bit_utils.h"

#include <stdint.h>
#include <stdbool.h>


uint64_t trap_capture_time;

typedef enum {
    INSTRUCTION_ADDRESS_MISALIGNED,
    INSTRUCTION_ACCESS_FAULT,
    ILLEGAL_INSTRUCTION,
    BREAKPOINT,
    LOAD_ADDRESS_MISALIGNED,
    LOAD_ACCESS_FAULT,
    STORE_AMO_ADDRESS_MISALIGNED,
    STORE_AMO_ACCESS_FAULT,
    ENVIRONMENT_CALL_FROM_U_MODE,
    ENVIRONMENT_CALL_FROM_S_MODE,
    INSTRUCTION_PAGE_FAULT,
    LOAD_PAGE_FAULT,
    STORE_AMO_PAGE_FAULT,
    USER_SOFTWARE_INTERRUPT,
    SUPERVISOR_SOFTWARE_INTERRUPT,
    USER_TIMER_INTERRUPT,
    SUPERVISOR_TIMER_INTERRUPT,
    USER_EXTERNAL_INTERRUPT,
    SUPERVISOR_EXTERNAL_INTERRUPT,
    RESERVED_OR_UNKNOWN
} TrapCause;

const char* trap_string_table[] = {
        "Instruction Address Misaligned",
        "Instruction Access Fault",
        "Illegal Instruction",
        "Breakpoint",
        "Load Address Misaligned",
        "Load Access Fault",
        "Store Amo Address Fault",
        "Store Amo Access Fault",
        "Environment Call From U Mode",
        "Environment Call From S Mode",
        "Instruction Page Fault",
        "Load Page Fault",
        "Store AMO Page Fault",
        "User Software Interrupt",
        "Supervisor Software Interrupt",
        "User Timer Interrupt",
        "Supervisor Timer Interrupt",
        "user External Interrupt",
        "Supervisor External Interrupt",
        "Reserved or Unknown"
};

uint32_t handle_instruction_address_misaligned_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: abort
    return sepc;
}

uint32_t handle_instruction_access_fault_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: abort
    return sepc;
}

uint32_t handle_illegal_instruction_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: abort
    return sepc;
}

uint32_t handle_breakpoint_exception(RiscvGPRS* regs, uint32_t sepc) {
    // handle system call emulation for supervisor mode
    time_schedule_next_timer(TIMER_TICK_INTERVAL);
    uint32_t new_sepc = syscall_execute(regs, sepc);
    return new_sepc;
}

uint32_t handle_load_address_misaligned_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: abort
    return sepc;
}

uint32_t handle_load_access_fault_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: abort
    return sepc;
}

uint32_t handle_store_amo_address_misaligned_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: abort?
    return sepc;
}

uint32_t handle_store_amo_access_fault_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: abort?
    return sepc;
}

uint32_t handle_ecall_from_user_mode_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: possible handle syscalls
    return sepc;
}

uint32_t handle_ecall_from_supervisor_mode_exception(RiscvGPRS* regs, uint32_t sepc) {
    schedule(regs, sepc);
    return sepc; // won't get here
}

uint32_t handle_instruction_page_fault_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: forward to corresponding pager
    sys_panic("page fault exception");
    return sepc;
}

uint32_t handle_load_page_fault_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: forward to corresponding pager
    sys_panic("page fault exception");
    return sepc;
}

uint32_t handle_store_amo_page_fault_exception(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: forward to corresponding pager
    sys_panic("page fault exception");
    return sepc;
}

uint32_t handle_user_software_interrupt(RiscvGPRS* regs, uint32_t sepc) {
    return sepc;
}

uint32_t handle_supervisor_software_interrupt(RiscvGPRS* regs, uint32_t sepc) {
    return sepc;
}

uint32_t handle_user_timer_interrupt(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: ??
    return sepc;
}

uint32_t handle_supervisor_timer_interrupt(RiscvGPRS* regs, uint32_t sepc) {
    uint32_t uptime_secs = time_secs_since_boot();
    uint32_t uptime_msecs = time_msecs_since_boot();
    kprintf(K_DEBUG,
            "system: uptime: msecs %u | %u second(s)\n",
            uptime_msecs, uptime_secs);
    time_schedule_next_timer(TIMER_TICK_INTERVAL);
    sched_run_rr_scheduler(regs, sepc);
    return sepc;
}

uint32_t handle_user_external_interrupt(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: handle possible device driver interrupt
    return sepc;
}

uint32_t handle_supervisor_external_interrupt(RiscvGPRS* regs, uint32_t sepc) {
    // TODO: handle possible device driver interrupt
    return sepc;
}

uint32_t (*trap_handlers[24]) (RiscvGPRS *, uint32_t);

TrapCause interrupt_cause(uint32_t trap_code) {
    if (trap_code == 0)
        return USER_SOFTWARE_INTERRUPT;
    else if (trap_code == 1)
        return SUPERVISOR_SOFTWARE_INTERRUPT;
    else if (trap_code == 2 || trap_code == 3)
        return RESERVED_OR_UNKNOWN;
    else if (trap_code == 4)
        return USER_TIMER_INTERRUPT;
    else if (trap_code == 5)
        return SUPERVISOR_TIMER_INTERRUPT;
    else if (trap_code >= 6 && trap_code <= 7)
        return RESERVED_OR_UNKNOWN;
    else if (trap_code == 8)
        return USER_EXTERNAL_INTERRUPT;
    else if (trap_code == 9)
        return SUPERVISOR_EXTERNAL_INTERRUPT;
    else
        return RESERVED_OR_UNKNOWN;
}

TrapCause exception_cause(uint32_t trap_code) {
    if (trap_code == 0)
        return INSTRUCTION_ADDRESS_MISALIGNED;
    else if (trap_code == 1)
        return INSTRUCTION_ACCESS_FAULT;
    else if (trap_code == 2)
        return ILLEGAL_INSTRUCTION;
    else if (trap_code == 3)
        return BREAKPOINT;
    else if (trap_code == 4)
        return LOAD_ADDRESS_MISALIGNED;
    else if (trap_code == 5)
        return LOAD_ACCESS_FAULT;
    else if (trap_code == 6)
        return STORE_AMO_ADDRESS_MISALIGNED;
    else if (trap_code == 7)
        return STORE_AMO_ACCESS_FAULT;
    else if (trap_code == 8)
        return ENVIRONMENT_CALL_FROM_U_MODE;
    else if (trap_code == 9)
        return ENVIRONMENT_CALL_FROM_S_MODE;
    else if (trap_code >= 10 && trap_code <= 11)
        return RESERVED_OR_UNKNOWN;
    else if (trap_code == 12)
        return INSTRUCTION_PAGE_FAULT;
    else if (trap_code == 13)
        return LOAD_PAGE_FAULT;
    else if (trap_code == 14)
        return RESERVED_OR_UNKNOWN;
    else if (trap_code == 15)
        return STORE_AMO_PAGE_FAULT;
    else
        return RESERVED_OR_UNKNOWN;
}

TrapCause trap_read_cause(uint32_t scause_reg) {
    bool is_interrupt = bits(scause_reg, 31, 1);
    uint32_t trap_code = bits(scause_reg, 0, 31);
    if (is_interrupt) {
        return interrupt_cause(trap_code);
    } else {
        return exception_cause(trap_code);
    }
}

void supervisor_handle_trap(RiscvGPRS * regs) {
    uint32_t scause = scause_r_csr();
    uint32_t sepc = sepc_r_csr();
    TrapCause cause = trap_read_cause(scause);
    kprintf(K_DEBUG, "system [interrupt]: caught %s at PC %p\n",
            trap_string_table[cause], sepc);
    // TODO verify cause is in range?
    uint32_t new_sepc = (*trap_handlers[cause])(regs, sepc);
    sepc_w_csr(new_sepc);
}

void setup_trap_handlers() {
    trap_handlers[USER_SOFTWARE_INTERRUPT] = handle_user_software_interrupt;
    trap_handlers[SUPERVISOR_SOFTWARE_INTERRUPT] = handle_supervisor_software_interrupt;
    trap_handlers[USER_TIMER_INTERRUPT] = handle_user_timer_interrupt;
    trap_handlers[SUPERVISOR_TIMER_INTERRUPT] = handle_supervisor_timer_interrupt;
    trap_handlers[USER_EXTERNAL_INTERRUPT] = handle_user_external_interrupt;
    trap_handlers[SUPERVISOR_EXTERNAL_INTERRUPT] = handle_supervisor_external_interrupt;
    trap_handlers[INSTRUCTION_ADDRESS_MISALIGNED] = handle_instruction_address_misaligned_exception;
    trap_handlers[INSTRUCTION_ACCESS_FAULT] = handle_instruction_access_fault_exception;
    trap_handlers[ILLEGAL_INSTRUCTION] = handle_illegal_instruction_exception;
    trap_handlers[BREAKPOINT] = handle_breakpoint_exception;
    trap_handlers[LOAD_ADDRESS_MISALIGNED] = handle_load_address_misaligned_exception;
    trap_handlers[LOAD_ACCESS_FAULT] = handle_load_access_fault_exception;
    trap_handlers[STORE_AMO_ADDRESS_MISALIGNED] = handle_store_amo_address_misaligned_exception;
    trap_handlers[STORE_AMO_ACCESS_FAULT] = handle_store_amo_access_fault_exception;
    trap_handlers[ENVIRONMENT_CALL_FROM_U_MODE] = handle_ecall_from_user_mode_exception;
    trap_handlers[ENVIRONMENT_CALL_FROM_S_MODE] = handle_ecall_from_supervisor_mode_exception;
    trap_handlers[INSTRUCTION_PAGE_FAULT] = handle_instruction_page_fault_exception;
    trap_handlers[LOAD_PAGE_FAULT] = handle_load_page_fault_exception;
    trap_handlers[STORE_AMO_PAGE_FAULT] = handle_store_amo_page_fault_exception;
}