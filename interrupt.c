#include "csr.h"
#include "kthread.h"
#include "bit_utils.h"
#include "sbi_relay.h"

#include <stdint.h>
#include <stdbool.h>

void thread_function_1() {
    int x = 25;
    while (true) {
        x += 5;
    }
}

void thread_function_2() {
    uint32_t y = 10;
    while (true) {
        y += 12;
    }
}


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

void handle_instruction_address_misaligned_exception(const RegisterGroup* regs) {
    // TODO: abort
}

void handle_instruction_access_fault_exception(const RegisterGroup* regs) {
    // TODO: abort
}

void handle_illegal_instruction_exception(const RegisterGroup* regs) {
    // TODO: abort
}

void handle_breakpoint_exception(const RegisterGroup* regs) {
    // TODO: ??
}

void handle_load_address_misaligned_exception(const RegisterGroup* regs) {
    // TODO: abort
}

void handle_load_access_fault_exception(const RegisterGroup* regs) {
    // TODO: abort
}

void handle_store_amo_address_misaligned_exception(const RegisterGroup* regs) {
    // TODO: abort?
}

void handle_store_amo_access_fault_exception(const RegisterGroup* regs) {
    // TODO: abort?
}

void handle_ecall_from_user_mode_exception(const RegisterGroup* regs) {
    // TODO: possible handle syscalls
}

void handle_ecall_from_supervisor_mode_exception(const RegisterGroup* regs) {
    // TODO: probably nothing, horizontal
}

void handle_instruction_page_fault_exception(const RegisterGroup* regs) {
    // TODO: forward to corresponding pager
}

void handle_load_page_fault_exception(const RegisterGroup* regs) {
    // TODO: forward to corresponding pager
}

void handle_store_amo_page_fault_exception(const RegisterGroup* regs) {
    // TODO: forward to corresponding pager
}

void handle_user_software_interrupt(const RegisterGroup* regs) {
    // TODO: ?
}

void handle_supervisor_software_interrupt(const RegisterGroup* regs) {
    // TODO: ?
}

void handle_user_timer_interrupt(const RegisterGroup* regs) {
    // TODO: adjust timer
}

void handle_supervisor_timer_interrupt(const RegisterGroup* regs) {
    // TODO: adjust timer
}

void handle_user_external_interrupt(const RegisterGroup* regs) {
    // TODO: ?
}

void handle_supervisor_external_interrupt(const RegisterGroup* regs) {
    // TODO: ?
}

void handle_any_trap_dummy(const RegisterGroup* regs) {  }

void (*trap_handlers[24]) (const RegisterGroup*);

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

void timer_reset() {
    uint64_t time = time_r_csr();
    struct sbiret timer_res = sbi_relay_set_timer(time+10000);
}

void supervisor_handle_trap(RegisterGroup* regs) {
    uint32_t scause = scause_r_csr();
    uint32_t sepc = sepc_r_csr();
    TrapCause cause = trap_read_cause(scause);
    // TODO verify cause is in range?
    (*trap_handlers[cause])(regs);
    sepc_w_csr(sepc);
    timer_reset();
    // return from interrupt
}

void trap_handling_init() {
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
    // configure timer interrupts
    uint32_t sstatus = sstatus_r_csr();
    uint32_t sie_val = sie_set_stie(0U, 0x1U);
    sie_val = sie_set_ssie(sie_val, 0x1U);
    sie_s_csr(sie_val);
    uint32_t new_sstatus = sstatus_set_sie(sstatus, 1U);
    uint64_t time = time_r_csr();
    struct sbiret timer_res = sbi_relay_set_timer(time+10000);
    sstatus_w_csr(new_sstatus);
}