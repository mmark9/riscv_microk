#ifndef RISCV_MICROK_TIME_H
#define RISCV_MICROK_TIME_H

#include <stdint.h>

void time_stop_timer();
uint32_t time_elapsed_trap_time();
uint32_t time_secs_since_boot();
uint32_t time_msecs_since_boot();
void time_capture_boot_time();
void time_schedule_next_timer(uint64_t expire_time);


#endif //RISCV_MICROK_TIME_H
