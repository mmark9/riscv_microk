#include "kprint.h"
#include "sbi_relay.h"

void panic(const char* reason) {
    kprintf("!!kernel panic!!: %s\n", reason);
    sbi_relay_system_reset(SBI_SHUTDOWN,
                           SBI_RESET_SYSTEM_FAILURE);
}