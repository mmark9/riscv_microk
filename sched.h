#ifndef RISCV_MICROK_SCHED_H
#define RISCV_MICROK_SCHED_H
#include "kthread.h"
#include <stdint.h>

int sched_demo_spawn_thread(void* entry_pc, void* arg);

#endif //RISCV_MICROK_SCHED_H
