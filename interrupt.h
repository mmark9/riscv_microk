#ifndef RISCV_MICROK_INTERRUPT_H
#define RISCV_MICROK_INTERRUPT_H

void supervisor_handle_trap(void);
void setup_trap_handlers(void);
void enable_interrupts();
void disable_interrupts();

#endif //RISCV_MICROK_INTERRUPT_H
