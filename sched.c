#include "sched.h"

#include <stdint.h>
#include <stdbool.h>

void load_context(RegisterGroup*, uint32_t);


int sched_spawn_thread(void* entry_pc, void* args) {
    // assume we already saved previous context
    // TODO: copy arguments to user stack
    // for testing purposes we will simply use the kernel address space
    // TODO: slab allocation to avoid overhead
    //KThread* thread = (KThread*)kmalloc(sizeof(KThread));
    KThread thread;
    // TODO: need a unique ID generator
    thread.thread_id = 1;
    load_context(&thread.regs, (uint32_t)entry_pc);
    // does not return
    return 0;
}
