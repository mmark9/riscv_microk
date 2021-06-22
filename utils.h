#ifndef RISCV_MICROK_UTILS_H
#define RISCV_MICROK_UTILS_H

#include <stdint.h>

#define max(a, b) ((a) >= (b) ? (a) : (b))
#define min(a, b) ((a) <= (b) ? (a) : (b))
void kmemcpy(void* dest, const void* src, uint32_t count);

#endif //RISCV_MICROK_UTILS_H
