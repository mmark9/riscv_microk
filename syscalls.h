#ifndef RISCV_MICROK_SYSCALLS_H
#define RISCV_MICROK_SYSCALLS_H

#include "ipc.h"
#include "arch.h"
#include "context.h"

#include <stdint.h>


void syscall_setup_table();

int32_t sys_do_yield();
int32_t sys_do_exit(uint32_t code);
int32_t sys_do_ipc_send_async(struct ipc_msg* msg);
int32_t sys_do_ipc_recv_async(struct ipc_msg* msg_out);
rvu_word syscall_execute(RiscvGPRS* regs, rvu_word sepc);

#endif //RISCV_MICROK_SYSCALLS_H
