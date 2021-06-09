#ifndef RISCV_MICROK_CONTEXT_H
#define RISCV_MICROK_CONTEXT_H

#include "arch.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    rvu_word x1_ra;
    rvu_word x2_sp;
    rvu_word x5_t0;
    rvu_word x6_t1;
    rvu_word x7_t2;
    rvu_word x8_s0;
    rvu_word x9_s1;
    rvu_word x10_a0;
    rvu_word x11_a1;
    rvu_word x12_a2;
    rvu_word x13_a3;
    rvu_word x14_a4;
    rvu_word x15_a5;
    rvu_word x16_a6;
    rvu_word x17_a7;
    rvu_word x18_s2;
    rvu_word x19_s3;
    rvu_word x20_s4;
    rvu_word x21_s5;
    rvu_word x22_s6;
    rvu_word x23_s7;
    rvu_word x24_s8;
    rvu_word x25_s9;
    rvu_word x26_s10;
    rvu_word x27_s11;
    rvu_word x28_t3;
    rvu_word x29_t4;
    rvu_word x30_t5;
    rvu_word x31_t6;
} RiscvGPRS;

typedef struct thread_context {
    RiscvGPRS regs;
    rvu_word pc;
} ThreadContext;

#define context_save_imm_thread_context(context,next_pc) \
{ \
    __asm__("mv tp, %0;" \
       "sw ra, 0(tp);"    \
       "sw sp, 4(tp);"    \
       "sw t0, 8(tp);"    \
       "sw t1, 12(tp);"   \
       "sw t2, 16(tp);"   \
       "sw s0, 20(tp);"   \
       "sw s1, 24(tp);"   \
       "sw a0, 28(tp);"   \
       "sw a1, 32(tp);"   \
       "sw a2, 36(tp);"   \
       "sw a3, 40(tp);"   \
       "sw a4, 44(tp);"   \
       "sw a5, 48(tp);"   \
       "sw a6, 52(tp);"   \
       "sw a7, 56(tp);"   \
       "sw s2, 60(tp);"   \
       "sw s3, 64(tp);"   \
       "sw s4, 68(tp);"   \
       "sw s5, 72(tp);"   \
       "sw s6, 76(tp);"   \
       "sw s7, 80(tp);"   \
       "sw s8, 84(tp);"   \
       "sw s9, 88(tp);"   \
       "sw s10, 92(tp);"  \
       "sw s11, 96(tp);"  \
       "sw t3, 100(tp);"  \
       "sw t4, 104(tp);"  \
       "sw t5, 108(tp);"  \
       "sw t6, 112(tp);"  \
       : /* no output */  \
       : "r" (&(context).regs)       \
       : "tp");            \
       context.pc = (rvu_word)(next_pc);    \
}

void context_save_thread_context(ThreadContext* dest,
                                 const RiscvGPRS* regs,
                                 rvu_word old_pc);

#endif //RISCV_MICROK_CONTEXT_H
