#ifndef RISCV_MICROK_TIME_H
#define RISCV_MICROK_TIME_H

#include "arch.h"
#include <stdint.h>

void time_stop_timer();
rvu_word time_elapsed_trap_time();
rvu_word time_secs_since_boot();
rvu_word time_msecs_since_boot();
void time_capture_boot_time();
void time_schedule_next_timer(uint64_t expire_time);


#endif //RISCV_MICROK_TIME_H
