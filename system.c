#include "csr.h"
#include "kprint.h"
#include "sbi_relay.h"
#include "system.h"

#include <stdbool.h>

void sys_ecall() {
    __asm__("ecall");
}
void sys_ebreak() {
    __asm__("ebreak");
}
void sys_kassert(bool condition) {
    if (!condition)
        sys_panic("assertion failed");
}
void sys_panic(const char* reason) {
    kprintf("!!kernel sys_panic!!: %s\n", reason);
    sbi_relay_system_reset(SBI_SHUTDOWN,
                           SBI_RESET_SYSTEM_FAILURE);
}
void sys_shutdown() {
    kprintf("system: sys_shutdown started\n");
    sbi_relay_system_reset(SBI_SHUTDOWN,
                           SBI_RESET_NO_REASON);
}
void sys_set_timer(uint64_t expire_time) {
    uint64_t time = time_r_csr();
    uint64_t new_time = time + expire_time;
    struct sbiret timer_res = sbi_relay_set_timer(new_time);
    sys_kassert(timer_res.error == SBI_SUCCESS);
}
void sys_stop_timer() {
    uint64_t new_time = -1ULL;
    struct sbiret timer_res = sbi_relay_set_timer(new_time);
    sys_kassert(timer_res.error == SBI_SUCCESS);
}
void sys_enable_supervisor_interrupts() {
    uint32_t sstatus = sstatus_r_csr();
    uint32_t new_sstatus = sstatus_set_sie(sstatus, 1U);
    sstatus_w_csr(new_sstatus);
}
void sys_disable_supervisor_interrupts() {
    uint32_t sstatus = sstatus_r_csr();
    uint32_t new_sstatus = sstatus_set_sie(sstatus, 0U);
    sstatus_w_csr(new_sstatus);
}
void sys_enable_supervisor_timer_interrupts() {
    uint32_t sie = sie_r_csr();
    uint32_t new_sie = sie_set_stie(sie, 1U);
    sie_w_csr(new_sie);
}
void sys_disable_supervisor_timer_interrupts() {
    uint32_t sie = sie_r_csr();
    uint32_t new_sie = sie_set_stie(sie, 0U);
    sie_w_csr(new_sie);
}
void sys_enable_supervisor_external_interrupts() {
    uint32_t sie = sie_r_csr();
    uint32_t new_sie = sie_set_seie(sie, 1U);
    sie_w_csr(new_sie);
}
void sys_disable_supervisor_external_interrupts() {
    uint32_t sie = sie_r_csr();
    uint32_t new_sie = sie_set_seie(sie, 0U);
    sie_w_csr(new_sie);
}
void sys_enable_supervisor_software_interrupts(){
    uint32_t sie = sie_r_csr();
    uint32_t new_sie = sie_set_ssie(sie, 1U);
    sie_w_csr(new_sie);
}
void sys_disable_supervisor_software_interrupts() {
    uint32_t sie = sie_r_csr();
    uint32_t new_sie = sie_set_ssie(sie, 0U);
    sie_w_csr(new_sie);
}
uint64_t sys_time() {
    return time_r_csr();
}
bool sys_supervisor_interrupts_enabled() {
    uint32_t sstatus = sstatus_r_csr();
    return sstatus_sie(sstatus) == 1;
}
bool sys_supervisor_timer_interrupts_enabled() {
    uint32_t sie = sie_r_csr();
    return sie_stie(sie) == 1;
}
bool sys_supervisor_software_interrupts_enabled() {
    uint32_t sie = sie_r_csr();
    return sie_ssie(sie) == 1;
}
bool sys_supervisor_external_interrupts_enabled() {
    uint32_t sie = sie_r_csr();
    return sie_seie(sie) == 1;
}