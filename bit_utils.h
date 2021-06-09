#ifndef RISCV_MICROK_BIT_UTILS_H
#define RISCV_MICROK_BIT_UTILS_H

#include "arch.h"

#include <stdint.h>

#define bits(v, pos, n) (((((0x1U << (rvu_word)(n)) - 1) << (rvu_word)(pos)) & (rvu_word)(v)) >> (rvu_word)(pos))
#define set_bits(x, v, pos, n)  (((~(((0x1U << (rvu_word)(n)) - 1) << (rvu_word)(pos))) & (x)) | ((rvu_word)(v) << (rvu_word)(pos)))

rvu_word little2big_l(rvu_word little);
rvu_word big2little_l(rvu_word big);
uint64_t big2little_dl(uint64_t big);


#endif //RISCV_MICROK_BIT_UTILS_H
