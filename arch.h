#ifndef RISCV_MICROK_ARCH_H
#define RISCV_MICROK_ARCH_H

#include <stdint.h>

// RVI = RISC-V Signed Word
// RVU = RISC-V Unsigned Word
#ifdef RV64
#define XLEN 64
typedef int64_t rvi_word;
typedef uint64_t rvu_word;
#else // RV32
#define XLEN 32
typedef uint32_t rvi_word;
typedef uint32_t rvu_word;
#endif

#endif //RISCV_MICROK_ARCH_H
