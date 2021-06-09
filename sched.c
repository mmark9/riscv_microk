#include "csr.h"
#include "time.h"
#include "sched.h"
#include "system.h"
#include "kprint.h"
#include "system.h"
#include "kmalloc.h"
#include "utils.h"
#include "page_table.h"
#include "interrupt.h"
#include "constants.h"
#include "simple_falloc.h"

#include <stdint.h>
#include <stdbool.h>

struct thread_tcb idle_thread;
struct thread_tcb* old_thread;
struct thread_tcb* current_thread;

uint32_t sched_time_msecs = 0;
uint32_t sched_cap_time_msecs = 0;

struct thread_tcb* thread_table[MAX_NUM_THREADS];

typedef struct {
    KThread head;
    KThread* tail;
    uint32_t count;
} SchedQueue;

// LOCK CANDIDATE
typedef struct {
    SchedQueue run_queue;
    SchedQueue block_queue;
    bool initialized;
    int32_t thread_id_counter;
} SchedState;

SchedState sched_state;

void load_context(RiscvGPRS *);

void switch_context_low(RiscvGPRS* );

void sched_run_idle_task() {
    sys_kassert(sched_state.initialized);
    for (uint32_t i = 0; i < UINT32_MAX; i++);
}

void sched_enqueue(struct thread_tcb* thread) {
    sys_kassert(thread != 0);
    sys_kassert(sched_state.initialized);
    SchedQueue* run_queue = &sched_state.run_queue;
    if (run_queue->head.next == 0) {
        run_queue->head.next = thread;
        thread->prev = &run_queue->head;
        thread->next = &run_queue->head;
        run_queue->tail = thread;
    } else {
        run_queue->tail->next = thread;
        thread->prev = run_queue->tail;
        thread->next = &run_queue->head;
        run_queue->head.prev = thread;
        run_queue->tail = thread;
    }
    run_queue->count += 1;
    thread->state = KTHREAD_READY_TO_RUN;
}

struct thread_tcb* sched_dequeue() {
    sys_kassert(sched_state.initialized);
    SchedQueue* run_queue = &sched_state.run_queue;
    if (run_queue->count == 0)
        return 0;
    sys_kassert(run_queue->head.next != 0);
    struct thread_tcb* thread = run_queue->head.next;
    run_queue->count -= 1;
    if (run_queue->count == 0) {
        run_queue->head.next = 0;
        run_queue->tail = 0;
    } else {
        run_queue->head.next = thread->next;
        run_queue->head.next->prev = &run_queue->head;
    }
    thread->next = 0;
    thread->prev = 0;
    return thread;
}

struct thread_tcb* sched_peek() {
    sys_kassert(sched_state.initialized);
    SchedQueue* run_queue = &sched_state.run_queue;
    if (run_queue->count == 0)
        return 0;
    return run_queue->head.next;
}

void sched_init() {
    sched_state.run_queue.count = 0;
    sched_state.run_queue.head.thread_id = -1;
    sched_state.run_queue.head.next = 0;
    sched_state.run_queue.head.prev = 0;
    sched_state.run_queue.tail = 0;
    sched_state.initialized = true;
    sched_state.thread_id_counter = 0;
    sched_cap_time_msecs = time_msecs_since_boot();
    __asm__("li tp, 0"
            : /* no outputs */
            : /* no inputs */
            : "tp"
            );
}

void sched_thread_exit() {
    sys_kassert(sched_state.initialized);
    kprintf(K_DEBUG,
            "sched [exit]: thread %d exiting...\n",
            current_thread->thread_id);
    current_thread->flagged_delete = true;
    sys_ebreak();
}

void sched_update_thread_quantum(struct thread_tcb* tcb) {
    if (current_thread == 0) {
        kputs(K_ERROR, "sched: current_thread is null!\n");
        sys_kassert(current_thread != 0);
    }
    int32_t delta = time_msecs_since_boot() - sched_cap_time_msecs;
    tcb->quantum -= delta;
}

void sched_do_thread_cleanup() {
    if (current_thread != 0 && current_thread->flagged_delete) {
        kprintf(K_DEBUG,
                "sched: cleaning up thread %d\n",
                current_thread->thread_id);
        kfree((void*)current_thread->k_stack_ptr);
        // TODO: find a way to clean up thread objects
        // threads may be allocated on the stack which should not
        // be tied to the heap pool; alternatively kfree() should
        // avoid freeing non-heap memory
        //kfree(current_thread);
        current_thread = 0;
    }
}

void sched_run_scheduler(const RiscvGPRS* regs, rvu_word old_pc) {
    sched_do_thread_cleanup();
    schedule(regs, old_pc);
}

void sched_run_rr_scheduler(const RiscvGPRS* regs, rvu_word old_pc) {
    sched_do_thread_cleanup();
    if (current_thread != 0) {
        sched_update_thread_quantum(current_thread);
        if (current_thread->quantum <= 0) {
            kprintf(K_DEBUG,
                    "sched: preempting thread %d due to time slice\n",
                    current_thread->thread_id);
            current_thread->quantum = TASK_TIME_SLICE;
            sched_enqueue(current_thread);
            schedule(regs, old_pc);
        }
    } else {
        schedule(regs, old_pc);
    }
    sched_cap_time_msecs = time_msecs_since_boot();
}


void sched_init_thread(struct thread_tcb* tcb, void* func) {
    sys_kassert(tcb != 0);
    sys_kassert(sched_state.initialized);
    tcb->user_context.pc = (rvu_word)func;
    tcb->entry_pc = (rvu_word)func;
    tcb->thread_id = sched_state.thread_id_counter++;
    tcb->user_context.regs.x1_ra = (rvu_word)sched_thread_exit;
    tcb->k_stack_ptr = (rvu_word)kmalloc(STACK_SIZE);
    tcb->u_stack_ptr = (rvu_word)kmalloc(STACK_SIZE);
    sys_kassert(tcb->k_stack_ptr != 0);
    sys_kassert(tcb->u_stack_ptr != 0);
    tcb->k_stack = tcb->k_stack_ptr + STACK_SIZE;
    tcb->u_stack = tcb->u_stack_ptr + STACK_SIZE;
    tcb->user_context.regs.x2_sp = tcb->u_stack_ptr + STACK_SIZE;
    tcb->flagged_delete = false;
    tcb->quantum = TASK_TIME_SLICE;
    tcb->send_queue.count = 0;
    tcb->send_queue.head = 0;
    tcb->send_queue.tail = 0;
    tcb->prev_snd = 0;
    tcb->next_snd = 0;
    tcb->context_lvl = 0;
    tcb->blocked_flag = false;
    if (simple_falloc_free_count() == 0) {
        kprintf(K_ERROR,
                "sched [create_thread]: no frames "
                "available for thread %d address space\n", tcb->thread_id);
        sys_kassert(false);
    }
    tcb->root_page = simple_falloc_alloc();
    sys_kassert(tcb->root_page != 0);
    // we can clone the kernel address space at this point
    // to avoid copying for every switch but this is less flexible
    // however, its inefficient to clone on every switch so we should
    // avoid changing kernel address space
    mem_clone_kernel_address_space(tcb->root_page);
    thread_table[tcb->thread_id] = tcb;
}

void sched_cleanup_thread(struct thread_tcb* tcb) {
    sys_kassert(tcb != 0);
    sys_kassert(sched_state.initialized);
    kfree((void*)tcb->user_context.regs.x2_sp);
}

void schedule(const RiscvGPRS* regs, rvu_word old_pc) {
    // this is only called during interrupt
    sys_kassert(sched_state.initialized);
    struct thread_tcb* tmp = sched_dequeue();
    if (tmp != 0 && current_thread != 0 && tmp->thread_id == current_thread->thread_id) {
        kprintf(K_DEBUG,
                "sched: avoiding context "
                "switch to same thread (%d)\n", tmp->thread_id);
        return;
    }
    if (tmp != 0 && current_thread != 0) {
        uint32_t old_thread_id = current_thread->thread_id;
        kprintf(K_DEBUG,
                "sched: switching from thread %d to thread %d\n",
                old_thread_id, tmp->thread_id);
        // save the old context
        if (regs != 0)
            context_save_thread_context(&current_thread->user_context, regs, old_pc);
    } else if (tmp != 0) {
        kprintf(K_DEBUG,
                "sched: switching to thread %d\n",
                tmp->thread_id);
    } else {
        sys_panic("scheduler could not find new thread to run");
    }
    sched_set_current_thread(tmp);
    sched_time_msecs = time_msecs_since_boot();
    sched_cap_time_msecs = sched_time_msecs;
    // at this point we can switch address spaces
    kprintf(K_DEBUG,
            "sched: switching to address space of thread %d\n",
            current_thread->thread_id);
    page_table_set_root_page(current_thread->root_page);
    if (current_thread->blocked_flag) {
        sepc_w_csr(current_thread->kernel_context.pc);
        current_thread->blocked_flag = false;
        current_thread->state = KTHREAD_KERNEL_RUNNING;
        // prevent interrupts from being enabled
        // when returning to kernel mode
        sys_disable_interrupts_for_next_context();
        load_context(&tmp->kernel_context.regs);
    } else {
        sepc_w_csr(current_thread->user_context.pc);
        // returning to the user implies that context level is 0
        current_thread->context_lvl = 0;
        load_context(&tmp->user_context.regs);
    }
}

struct thread_tcb* sched_find_blocked_thread(int32_t thread_id) {
    sys_kassert(sched_state.initialized);
    SchedQueue* block_queue = &sched_state.block_queue;
    if (block_queue->count == 0)
        return 0;
    sys_kassert(block_queue->head.next != 0);
    struct thread_tcb* thread = block_queue->head.next;
    do {
        if (thread->thread_id == thread_id)
            return thread;
        thread = thread->next;
    } while (thread != &block_queue->head);
    return 0;
}

bool sched_thread_is_blocked(int32_t thread_id) {
    struct thread_tcb* tmp = sched_find_blocked_thread(thread_id);
    return tmp != 0;
}

void sched_enqueue_blocked_thread(struct thread_tcb* thread) {
    sys_kassert(thread != 0);
    SchedQueue* block_queue = &sched_state.block_queue;
    kprintf(K_DEBUG,
            "sched [block]: thread %d is now blocked\n",
            thread->thread_id);
    if (block_queue->head.next == 0) {
        block_queue->head.next = thread;
        thread->prev = &block_queue->head;
        thread->next = &block_queue->head;
        block_queue->tail = thread;
    } else {
        block_queue->tail->next = thread;
        thread->prev = block_queue->tail;
        thread->next = &block_queue->head;
        block_queue->head.prev = thread;
        block_queue->tail = thread;
    }
    block_queue->count += 1;
    thread->state = KTHREAD_BLOCKED;
}

void sched_dequeue_blocked_thread(struct thread_tcb* thread) {
    thread->prev->next = thread->next;
    thread->next->prev = thread->prev;
    thread->next = thread->prev = 0;
    SchedQueue* block_queue = &sched_state.block_queue;
    block_queue->count -= 1;
    if (block_queue->count == 0) {
        block_queue->head.next = 0;
        block_queue->tail = 0;
    }
}

void sched_block_thread(const RiscvGPRS* regs, rvu_word next_pc) {
    if (current_thread->state == KTHREAD_BLOCKED) {
        kprintf(K_DEBUG,
                "sched [block]: thread %d is already blocked\n",
                current_thread->thread_id);
        return;
    }
    // set this to signal that the kernel
    // context should be restored after
    // unblocking
    current_thread->blocked_flag = true;
    sys_kassert(sched_state.initialized);
    kprintf(K_DEBUG,
            "sched [block]: blocking thread %u\n",
            current_thread->thread_id);
    current_thread->state = KTHREAD_BLOCKED;
    sched_enqueue_blocked_thread(current_thread);
    // switch to another thread
    schedule(regs, next_pc);
}

bool sched_unblock_thread(int32_t thread_id) {
    sys_kassert(sched_state.initialized);
    struct thread_tcb* thread = sched_find_blocked_thread(thread_id);
    if (thread == 0) {
        kprintf(K_DEBUG,
                "sched [unblock]: could not find thread %u in block queue\n", thread_id);
        return false;
    }
    sched_dequeue_blocked_thread(thread);
    kprintf(K_DEBUG,
            "sched [unblock]: adding thread %u to run queue\n", thread_id);
    sched_enqueue(thread);
    return true;
}

struct thread_tcb* sched_lookup_thread(int32_t thread_id) {
    if (thread_id >= MAX_NUM_THREADS) {
        kprintf(K_DEBUG,
                "sched [lookup]: thread id %d of range [0, %u]\n",
                thread_id, MAX_NUM_THREADS);
        return 0;
    }
    return thread_table[thread_id];
}

void sched_set_current_thread(struct thread_tcb* thread) {
    current_thread = thread;
    __asm__("mv tp, %0;"
    : /* no outputs */
    : "r" (current_thread)
    : "tp"
    );
}