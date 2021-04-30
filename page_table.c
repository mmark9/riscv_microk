#include "csr.h"
#include "constants.h"
#include "bit_utils.h"
#include "page_table.h"

#include <stdint.h>


static bool paging_enabled;
static uint32_t* page_table_current_lvl1;

bool paging_is_enabled() {
    return paging_enabled;
}

void page_table_simple_flush_tlb() {
    __asm__("sfence.vma zero, zero");
}

uint32_t sv32_pte(uint32_t paddr, bool user_access,
                  bool can_read, bool can_write,
                  bool can_exec, bool global, bool valid) {
    uint32_t pte = (paddr >> 12U) << 10U;
    pte = sv32_set_user_can_access(pte, user_access);
    pte = sv32_set_can_execute(pte, can_exec);
    pte = sv32_set_can_write(pte, can_write);
    pte = sv32_set_can_read(pte, can_read);
    pte = sv32_set_is_global(pte, global);
    pte = sv32_set_valid(pte, valid);
    return pte;
}

uint32_t sv32_user_pte(uint32_t paddr, bool can_read,
                       bool can_write, bool can_exec, bool valid) {
    return sv32_pte(paddr, true, can_read,
                    can_write, can_exec, false, valid);
}

uint32_t sv32_kernel_pte(uint32_t paddr, bool can_read,
                         bool can_write, bool can_exec, bool valid) {
    return sv32_pte(paddr, false, can_read,
                    can_write, can_exec, false, valid);
}

uint32_t sv32_kernel_pte_pointer(uint32_t paddr, bool valid) {
    return sv32_pte(paddr, false, false,
                    false, false, false, valid);
}

uint32_t sv32_user_pte_pointer(uint32_t paddr, bool valid) {
    return sv32_pte(paddr, true, false,
                    false, false, false, valid);
}




