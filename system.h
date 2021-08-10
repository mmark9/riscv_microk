#ifndef RISCV_MICROK_SYSTEM_H
#define RISCV_MICROK_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MACHINE_MODE = 0,
    SUPERVISOR_MODE,
    USER_MODE
} PrivilegeMode;

typedef struct {
    uint32_t mem_base;
    uint32_t mem_size;
    uint32_t core_id;
} PlatformInfo;

void sys_shutdown();
void sys_set_platform_info(PlatformInfo* info);
PlatformInfo sys_platform_info();
void sys_kassert(bool condition);
void sys_panic(const char* reason);
void sys_ecall();
void sys_ebreak();
void sys_halt();
void sys_tlb_flush_all();
void sys_stop_timer();
void sys_enable_supervisor_interrupts();
void sys_disable_supervisor_interrupts();
void sys_enable_supervisor_timer_interrupts();
void sys_disable_supervisor_timer_interrupts();
void sys_enable_supervisor_external_interrupts();
void sys_disable_supervisor_external_interrupts();
void sys_enable_supervisor_software_interrupts();
void sys_disable_supervisor_software_interrupts();
void sys_initialize_privilege_mode_status();
void sys_prepare_switch_to_user();
void sys_prepare_switch_to_supervisor();
void sys_disable_interrupts_for_next_context();
PrivilegeMode sys_target_privilege_mode();
bool sys_supervisor_interrupts_enabled();
bool sys_supervisor_timer_interrupts_enabled();
bool sys_supervisor_software_interrupts_enabled();
bool sys_supervisor_external_interrupts_enabled();
int32_t sys_core_id();
void sys_set_core_id(int32_t core_id);
void sys_return_from_blocked_status();
void sys_trigger_supervisor_software_interrupt();
void sys_clear_supervisor_software_interrupt();

#endif //RISCV_MICROK_SYSTEM_H
