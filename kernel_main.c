#include "csr.h"
#include "sbi_relay.h"

#include <stdint.h>
#include <stdbool.h>

extern void halt_system(void);

enum trap_cause {
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
};

enum trap_cause trap_read_cause(uint32_t scause_reg) {
    if (scause_interrupt(scause_reg)) {
        switch (scause_except_code(scause_reg)) {
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
        switch (scause_except_code(scause_reg)) {
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
    return 0;
}

void kernel_main(
        uint32_t boot_hart_id,
		void* config_ptr,
		int32_t config_type) {
    // loop for now....

    uint32_t sstatus = sstatus_r_csr();
    uint32_t uie = sstatus_uie(sstatus);
    uint32_t sie = sstatus_sie(sstatus);
    uint32_t upie = sstatus_upie(sstatus);
    uint32_t spie = sstatus_spie(sstatus);
    uint32_t spp = sstatus_spp(sstatus);
    uint32_t fs = sstatus_fs(sstatus);
    uint32_t xs = sstatus_xs(sstatus);
    uint32_t sum = sstatus_sum(sstatus);
    uint32_t mxr = sstatus_mxr(sstatus);
    uint32_t sd = sstatus_sd(sstatus);
    struct sbiret impl_id = sbi_relay_get_impl_id();
    struct sbiret march_id = sbi_relay_get_marchid();
    struct sbiret vendor_id = sbi_relay_get_mvendorid();
    struct sbiret shutdown_ret = sbi_relay_system_reset(SBI_SHUTDOWN,
            SBI_RESET_NO_REASON);
    while (true) {
        continue;
    }
}

