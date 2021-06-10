#ifndef RISCV_MICROK_BIT_UTILS_H
#define RISCV_MICROK_BIT_UTILS_H

#include "arch.h"

#include <stdint.h>

#ifdef RV64
#define bits(v, pos, n) (((((0x1LLU << (rvu_word)(n)) - 1) << (rvu_word)(pos)) & (rvu_word)(v)) >> (rvu_word)(pos))
#define set_bits(x, v, pos, n)  (((~(((0x1LLU << (rvu_word)(n)) - 1) << (rvu_word)(pos))) & (x)) | ((rvu_word)(v) << (rvu_word)(pos)))
#else
#define bits(v, pos, n) (((((0x1U << (rvu_word)(n)) - 1) << (rvu_word)(pos)) & (rvu_word)(v)) >> (rvu_word)(pos))
#define set_bits(x, v, pos, n)  (((~(((0x1U << (rvu_word)(n)) - 1) << (rvu_word)(pos))) & (x)) | ((rvu_word)(v) << (rvu_word)(pos)))
#endif

uint32_t little2big_l(uint32_t little);
uint32_t big2little_l(uint32_t big);
uint64_t big2little_dl(uint64_t big);


#endif //RISCV_MICROK_BIT_UTILS_H
