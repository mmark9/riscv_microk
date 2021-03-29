#ifndef RISCV_MICROK_BIT_UTILS_H
#define RISCV_MICROK_BIT_UTILS_H

#include <stdint.h>

#define bits(v, pos, n) (((((0x1U << (uint32_t)n) - 1) << (uint32_t)pos) & (uint32_t)v) >> (uint32_t)pos)
#define set_bits(x, v, pos, n)  (((~(((0x1U << (uint32_t)n) - 1) << (uint32_t)pos)) & x) | ((uint32_t)v << (uint32_t)pos))

uint32_t little2big_l(uint32_t little);
uint32_t big2little_l(uint32_t big);
uint32_t big2little_dl(uint64_t big);


#endif //RISCV_MICROK_BIT_UTILS_H
