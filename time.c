#include "csr.h"
#include "system.h"
#include "sbi_relay.h"
#include "constants.h"


uint64_t boot_hz_cap = 0;

rvu_word time_secs_since_boot() {
    uint64_t new_time_hz = time_r_csr();
    uint64_t delta_hz = new_time_hz - boot_hz_cap;
    rvu_word seconds = delta_hz / TIMER_FREQUENCY_BASE;
    return seconds;
}

rvu_word time_msecs_since_boot() {
    uint64_t new_time_hz = time_r_csr();
    uint64_t delta_hz = new_time_hz - boot_hz_cap;
    rvu_word ms = delta_hz / TIMER_CYCLES_PER_MSEC;
    return ms;
}

void time_capture_boot_time() {
    boot_hz_cap = time_r_csr();
}

void time_schedule_next_timer(uint64_t expire_time) {
    uint64_t time = time_r_csr();
    uint64_t new_time = time + expire_time;
    struct sbiret timer_res = sbi_relay_set_timer(new_time);
    sys_kassert(timer_res.error == SBI_SUCCESS);
}
void time_stop_timer() {
    uint64_t new_time = -1ULL;
    struct sbiret timer_res = sbi_relay_set_timer(new_time);
    sys_kassert(timer_res.error == SBI_SUCCESS);
}


