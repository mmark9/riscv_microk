#ifndef RISCV_MICROK_SCHED_H
#define RISCV_MICROK_SCHED_H
#include "context.h"
#include <stdint.h>

typedef enum ThreadStatus {
    KTHREAD_CREATED = 0,
    KTHREAD_READY_TO_RUN,
    KTHREAD_USER_RUNNING,
    KTHREAD_KERNEL_RUNNING,
    KTHREAD_ASLEEP,
    KTHREAD_PREEMPTED
} KThreadState;

typedef struct thread_tcb {
    int32_t thread_id;
    uint32_t u_stack_ptr;
    uint32_t k_stack_ptr;
    uint32_t quantum;
    uint32_t priority;
    uint32_t entry_pc;
    uint32_t pc;
    RiscvGPRS regs;
    KThreadState state;
    uint32_t root_page;
    struct thread_tcb* next;
    struct thread_tcb* prev;
    // for testing
    bool flagged_delete;
} KThread;

void sched_init();
void schedule(const RiscvGPRS* prev_context, uint32_t pc);
void sched_init_thread(struct thread_tcb* tcb, void* func);
void sched_run_scheduler(const RiscvGPRS* regs, uint32_t old_pc);
void sched_enqueue(struct thread_tcb* thread);
void sched_run_rr_scheduler(const RiscvGPRS* regs, uint32_t old_pc);

#endif //RISCV_MICROK_SCHED_H
