#include "sched.h"
#include "system.h"
#include "kprint.h"
#include "kmalloc.h"
#include "interrupt.h"

#include <stdint.h>
#include <stdbool.h>

bool thread_spawned;
KThread* current_thread;

void load_context(RegisterGroup*);


void sched_demo_exit_shutdown() {
    kprintf("sched > demo: shutting down..\n");
    shutdown();
}


int sched_demo_spawn_thread(void* entry_pc, void* args) {
    // assume we already saved previous context
    // TODO: copy arguments to user stack
    // for testing purposes we will simply use the kernel address space
    // TODO: slab allocation to avoid overhead
    //current_thread = &thread;
    // TODO: need a unique ID generator
    if (!thread_spawned) {
        KThread* thread = (KThread*)kmalloc(sizeof(KThread));
        thread->thread_id = 1;
        thread->regs.pc = (uint32_t)entry_pc;
        thread->regs.x1_ra = (uint32_t)sched_demo_exit_shutdown;
        kprintf("sched > demo: spawning thread | id=%d | function = %p\n",
                thread->thread_id,  entry_pc);
        thread_spawned = true;
        current_thread = thread;
        // does not return
        disable_interrupts();
        load_context(&thread->regs);
    } else {
        disable_interrupts();
    }
    return 0;
}