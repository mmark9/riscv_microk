#ifndef RISCV_MICROK_SYSTEM_H
#define RISCV_MICROK_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

void sys_shutdown();
void sys_kassert(bool condition);
void sys_panic(const char* reason);
void sys_ecall();
void sys_ebreak();
void sys_stop_timer();
void sys_enable_supervisor_interrupts();
void sys_disable_supervisor_interrupts();
void sys_enable_supervisor_timer_interrupts();
void sys_disable_supervisor_timer_interrupts();
void sys_enable_supervisor_external_interrupts();
void sys_disable_supervisor_external_interrupts();
void sys_enable_supervisor_software_interrupts();
void sys_disable_supervisor_software_interrupts();
void sys_set_timer(uint64_t expire_time);
uint64_t sys_time();
bool sys_supervisor_interrupts_enabled();
bool sys_supervisor_timer_interrupts_enabled();
bool sys_supervisor_software_interrupts_enabled();
bool sys_supervisor_external_interrupts_enabled();

#endif //RISCV_MICROK_SYSTEM_H
