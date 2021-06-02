#ifndef RISCV_MICROK_CONTEXT_H
#define RISCV_MICROK_CONTEXT_H


#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t x1_ra;
    uint32_t x2_sp;
    uint32_t x5_t0;
    uint32_t x6_t1;
    uint32_t x7_t2;
    uint32_t x8_s0;
    uint32_t x9_s1;
    uint32_t x10_a0;
    uint32_t x11_a1;
    uint32_t x12_a2;
    uint32_t x13_a3;
    uint32_t x14_a4;
    uint32_t x15_a5;
    uint32_t x16_a6;
    uint32_t x17_a7;
    uint32_t x18_s2;
    uint32_t x19_s3;
    uint32_t x20_s4;
    uint32_t x21_s5;
    uint32_t x22_s6;
    uint32_t x23_s7;
    uint32_t x24_s8;
    uint32_t x25_s9;
    uint32_t x26_s10;
    uint32_t x27_s11;
    uint32_t x28_t3;
    uint32_t x29_t4;
    uint32_t x30_t5;
    uint32_t x31_t6;
} RiscvGPRS;

typedef struct thread_context {
    RiscvGPRS regs;
    uint32_t pc;
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
       (context).pc = (uint32_t)(next_pc);    \
}

void context_save_thread_context(ThreadContext* dest,
                                 const RiscvGPRS* regs,
                                 uint32_t old_pc);

#endif //RISCV_MICROK_CONTEXT_H
