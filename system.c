#include "kprint.h"
#include "sbi_relay.h"

#include <stdbool.h>

void panic(const char* reason) {
    kprintf("!!kernel panic!!: %s\n", reason);
    sbi_relay_system_reset(SBI_SHUTDOWN,
                           SBI_RESET_SYSTEM_FAILURE);
}

void shutdown() {
    kprintf("system: shutdown started\n");
    sbi_relay_system_reset(SBI_SHUTDOWN, SBI_RESET_NO_REASON);
}

void kassert(bool condition) {
    if (!condition)
        panic("assertion failed");
}