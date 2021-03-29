#ifndef RISCV_MICROK_KTHREAD_H
#define RISCV_MICROK_KTHREAD_H
#include <stdint.h>

typedef struct {
    uint32_t pc;
    uint32_t x1_ra;
    uint32_t x2_sp;
    uint32_t x3_gp;
    uint32_t x4_tp;
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
} RegisterGroup;

typedef enum ThreadStatus {
    KTHREAD_CREATED = 0,
    KTHREAD_READY_TO_RUN,
    KTHREAD_USER_RUNNING,
    KTHREAD_KERNEL_RUNNING,
    KTHREAD_ASLEEP,
    KTHREAD_PREEMPTED
} KThreadState;

typedef struct {
    uint32_t thread_id;
    uint32_t u_stack_ptr;
    uint32_t k_stack_ptr;
    RegisterGroup regs;
    uint32_t quantum;
    uint32_t priority;
} KThread;
#endif //RISCV_MICROK_KTHREAD_H
