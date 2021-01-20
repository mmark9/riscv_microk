#include "csr.h"
#include <stdint.h>
#include <stdbool.h>

extern void halt_system(void);

typedef enum {
    INSTRUCTION_ADDRESS_MISALIGNED = 0,
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
} trap_cause_t;

trap_cause_t trap_read_cause(tcause_csr_t cause_reg) {
    if (cause_reg.fields.was_caused_by_interrupt) {
        switch (cause_reg.fields.exception_code) {
            case 0:
                return USER_SOFTWARE_INTERRUPT;
            case 1:
                return SUPERVISOR_SOFTWARE_INTERRUPT;
            case 2:
            case 3:
                return RESERVED_OR_UNKNOWN;
            case 4:
                return USER_TIMER_INTERRUPT;
            case 5:
                return SUPERVISOR_TIMER_INTERRUPT;
            case 6:
                return RESERVED_OR_UNKNOWN;
            case 8:
                return USER_EXTERNAL_INTERRUPT;
            case 9:
                return SUPERVISOR_EXTERNAL_INTERRUPT;
            default:
                return RESERVED_OR_UNKNOWN;
        }
    } else {
        switch (cause_reg.fields.exception_code) {
            case 0:
                return INSTRUCTION_ADDRESS_MISALIGNED;
            case 1:
                return INSTRUCTION_ACCESS_FAULT;
            case 2:
                return ILLEGAL_INSTRUCTION;
            case 3:
                return BREAKPOINT;
            case 4:
                return LOAD_ADDRESS_MISALIGNED;
            case 5:
                return LOAD_ACCESS_FAULT;
            case 6:
                return STORE_AMO_ADDRESS_MISALIGNED;
            case 7:
                return STORE_AMO_ACCESS_FAULT;
            case 8:
                return ENVIRONMENT_CALL_FROM_U_MODE;
            case 9:
                return ENVIRONMENT_CALL_FROM_S_MODE;
            case 10:
            case 11:
                return RESERVED_OR_UNKNOWN;
            case 12:
                return INSTRUCTION_PAGE_FAULT;
            case 13:
                return LOAD_PAGE_FAULT;
            case 14:
                return RESERVED_OR_UNKNOWN;
            case 15:
                return STORE_AMO_PAGE_FAULT;
            default:
                return RESERVED_OR_UNKNOWN;
        }
    }
}

uint32_t supervisor_handle_interrupt(void) {
    uint32_t sepc = 0;
    tcause_csr_t scause;
    riscv_read_csr_register(CSR_SEPC, &sepc);
    riscv_read_csr_register(CSR_SCAUSE, &scause.value);
    trap_cause_t tcause = trap_read_cause(scause);
    if (tcause == SUPERVISOR_TIMER_INTERRUPT) {
        return sepc;
    } else {
        sepc = (uint32_t) &halt_system;
        return sepc;
    }
}

void kernel_main(
        uint32_t boot_hart_id,
		void* config_ptr,
		int32_t config_type) {
    // loop for now....
    while (true) {
        continue;
    }
}

