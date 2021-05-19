#ifndef RISCV_MICROK_SYSTEM_H
#define RISCV_MICROK_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    MACHINE_MODE = 0,
    SUPERVISOR_MODE,
    USER_MODE
} PrivilegeMode;

void sys_shutdown();
void sys_kassert(bool condition);
void sys_panic(const char* reason);
void sys_ecall();
void sys_ebreak();
void sys_halt();
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
PrivilegeMode sys_target_privilege_mode();
bool sys_supervisor_interrupts_enabled();
bool sys_supervisor_timer_interrupts_enabled();
bool sys_supervisor_software_interrupts_enabled();
bool sys_supervisor_external_interrupts_enabled();

#endif //RISCV_MICROK_SYSTEM_H
