#include "csr.h"
#include "sched.h"
#include "interrupt.h"
#include "sbi_relay.h"

#include <stdint.h>
#include <stdbool.h>

bool thread_spawned;

extern void halt_system(void);

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
    uint32_t new_sstatus = sstatus_set_sie(sstatus, 1U);
    uint32_t sie_val = sie_set_stie(0U, 0x1U);
    sie_val = sie_set_ssie(sie_val, 0x1U);
    sie_s_csr(sie_val);
    uint64_t time = time_r_csr();
    struct sbiret timer_res = sbi_relay_set_timer(time+10000);
    sstatus_w_csr(new_sstatus);
    /*char* fake_ptr = (char*)0x10;
    char x = *fake_ptr;*/
    struct sbiret impl_id = sbi_relay_get_impl_id();
    struct sbiret march_id = sbi_relay_get_marchid();
    struct sbiret vendor_id = sbi_relay_get_mvendorid();
    /*struct sbiret shutdown_ret = sbi_relay_system_reset(SBI_SHUTDOWN,
            SBI_RESET_NO_REASON);*/
    while (true) {
        continue;
    }
}

