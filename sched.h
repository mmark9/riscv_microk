#ifndef RISCV_MICROK_SCHED_H
#define RISCV_MICROK_SCHED_H

#include "arch.h"
#include "context.h"

#include <stdint.h>

#define MAX_NUM_THREADS 128

typedef enum ThreadStatus {
    KTHREAD_CREATED = 0,
    KTHREAD_READY_TO_RUN,
    KTHREAD_USER_RUNNING,
    KTHREAD_KERNEL_RUNNING,
    KTHREAD_ASLEEP,
    KTHREAD_PREEMPTED,
    KTHREAD_BLOCKED
} KThreadState;

typedef struct thread_tcb {
    int32_t thread_id;
    rvu_word scratch1;
    rvu_word scratch2;
    rvu_word context_lvl;
    rvu_word u_stack;
    rvu_word k_stack;
    rvu_word u_stack_ptr;
    rvu_word k_stack_ptr;
    ThreadContext user_context;
    ThreadContext kernel_context;
    int32_t quantum;
    uint32_t priority;
    rvu_word entry_pc;
    KThreadState state;
    rvu_word root_page;
    struct thread_tcb* next;
    struct thread_tcb* prev;
    struct thread_tcb* next_snd;
    struct thread_tcb* prev_snd;
    // for testing
    bool flagged_delete;
    bool blocked_flag;
    struct {
        struct thread_tcb* head;
        struct thread_tcb* tail;
        uint32_t count;
    } send_queue;
    void* ipc_msg_buf_addr;
} KThread;

extern KThread* current_thread;

void sched_init();
void sched_set_current_thread(struct thread_tcb* thread);
bool sched_thread_is_blocked(int32_t thread_id);
void sched_block_thread(const RiscvGPRS* regs, rvu_word next_pc);
bool sched_unblock_thread(int32_t thread_id);
void schedule(const RiscvGPRS* prev_context, rvu_word pc);
void sched_init_thread(struct thread_tcb* tcb, void* func);
void sched_run_scheduler(const RiscvGPRS* regs, rvu_word old_pc);
void sched_enqueue(struct thread_tcb* thread);
void sched_run_rr_scheduler(const RiscvGPRS* regs, rvu_word old_pc);
struct thread_tcb* sched_lookup_thread(int32_t thread_id);

#endif //RISCV_MICROK_SCHED_H
