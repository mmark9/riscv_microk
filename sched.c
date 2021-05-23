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

typedef struct {
    KThread head;
    KThread* tail;
    uint32_t count;
} SchedQueue;

// LOCK CANDIDATE
typedef struct {
    SchedQueue run_queue;
    bool initialized;
    uint32_t thread_id_counter;
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
}

void sched_thread_exit() {
    sys_kassert(sched_state.initialized);
    kprintf("sched [exit]: thread %d exiting...\n",
            current_thread->thread_id);
    current_thread->flagged_delete = true;
    sys_ebreak();
}

void sched_update_thread_quantum(struct thread_tcb* tcb) {
    if (current_thread == 0) {
        kputs("sched: current_thread is null!\n");
        sys_kassert(current_thread != 0);
    }
    int32_t delta = time_msecs_since_boot() - sched_cap_time_msecs;
    tcb->quantum -= delta;
}

void sched_do_thread_cleanup() {
    if (current_thread != 0 && current_thread->flagged_delete) {
        kprintf("sched: cleaning up thread %d\n",
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

void sched_run_scheduler(const RiscvGPRS* regs, uint32_t old_pc) {
    sched_do_thread_cleanup();
    schedule(regs, old_pc);
}

void sched_run_rr_scheduler(const RiscvGPRS* regs, uint32_t old_pc) {
    sched_do_thread_cleanup();
    if (current_thread != 0) {
        sched_update_thread_quantum(current_thread);
        if (current_thread->quantum <= 0) {
            kprintf("sched: preempting thread %d due to time slice\n",
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
    tcb->pc = (uint32_t)func;
    tcb->entry_pc = (uint32_t)func;
    tcb->thread_id = sched_state.thread_id_counter++;
    tcb->regs.x1_ra = (uint32_t)sched_thread_exit;
    uint32_t stack_region = (uint32_t)kmalloc(STACK_SIZE);
    tcb->k_stack_ptr = stack_region;
    tcb->regs.x2_sp = stack_region + STACK_SIZE;
    tcb->flagged_delete = false;
    tcb->quantum = TASK_TIME_SLICE;
    if (simple_falloc_free_count() == 0) {
        kprintf("sched [create_thread]: no frames "
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
}

void sched_cleanup_thread(struct thread_tcb* tcb) {
    sys_kassert(tcb != 0);
    sys_kassert(sched_state.initialized);
    kfree((void*)tcb->regs.x2_sp);
}

void sched_save_thread_context(const RiscvGPRS* regs, uint32_t old_pc) {
    kmemcpy(&current_thread->regs, regs, sizeof(RiscvGPRS));
    current_thread->pc = old_pc;
}

void schedule(const RiscvGPRS* regs, uint32_t old_pc) {
    // this is only called during interrupt
    sys_kassert(sched_state.initialized);
    struct thread_tcb* tmp = sched_dequeue();
    if (tmp != 0 && current_thread != 0) {
        uint32_t old_thread_id = current_thread->thread_id;
        kprintf("sched: switching from thread %d to thread %d\n",
                old_thread_id, tmp->thread_id);
        // save the old context
        if (regs != 0)
            sched_save_thread_context(regs, old_pc);
    } else if (tmp != 0) {
        kprintf("sched: switching to thread %d\n",
                tmp->thread_id);
    } else {
        sys_panic("scheduler could not find new thread to run");
    }
    sepc_w_csr(tmp->pc);
    current_thread = tmp;
    sched_time_msecs = time_msecs_since_boot();
    sched_cap_time_msecs = sched_time_msecs;
    // at this point we can switch address spaces
    kprintf("sched: switching to address space of thread %d\n",
            current_thread->thread_id);
    page_table_set_root_page(current_thread->root_page);
    load_context(&tmp->regs);
}