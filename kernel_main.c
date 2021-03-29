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
    trap_handling_init();
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

