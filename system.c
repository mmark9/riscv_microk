#include "csr.h"
#include "kprint.h"
#include "sbi_relay.h"
#include "system.h"

#include <stdbool.h>

int32_t current_core_id = -1;
PrivilegeMode sys_privilege_mode;
PrivilegeMode sys_previous_privilege_mode;

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
void sys_halt() {
    for (;;);
}
void sys_tlb_flush_all() {
    __asm__("sfence.vma zero, zero");
}
void sys_panic(const char* reason) {
    kprintf("!!kernel sys_panic!!: %s\n", reason);
    sys_halt();
}
void sys_shutdown() {
    kprintf("system: sys_shutdown started\n");
    sbi_relay_system_reset(SBI_SHUTDOWN,
                           SBI_RESET_NO_REASON);
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
void sys_initialize_privilege_mode_status() {
    sys_previous_privilege_mode = MACHINE_MODE;
    sys_privilege_mode = SUPERVISOR_MODE;
}
void sys_prepare_switch_to_user() {
    uint32_t ssatus = sstatus_r_csr();
    uint32_t spp = sstatus_spp(ssatus);
    uint32_t new_sstatus = sstatus_set_spp(ssatus, 0);
    sstatus_w_csr(new_sstatus);
    // Note this won't be accurate until a return interrupt
    sys_previous_privilege_mode = sys_privilege_mode;
    sys_privilege_mode = USER_MODE;
}
PrivilegeMode sys_target_privilege_mode() {
    // target privilege mode may or may not correspond
    // to the effective privilege mode of the processor
    // RISC-V doesn't provide a means of checking so
    // this a compromise
    return sys_privilege_mode;
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
int32_t sys_core_id() {
    return current_core_id;
}
void sys_set_core_id(int32_t core_id) {
    current_core_id = core_id;
}