#include "context.h"


void context_save_thread_context(ThreadContext* dest,
                                 const RiscvGPRS* regs,
                                 rvu_word old_pc) {
    kmemcpy(&dest->regs, regs, sizeof(RiscvGPRS));
    dest->pc = old_pc;
}