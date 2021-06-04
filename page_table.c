#include "csr.h"
#include "kprint.h"
#include "constants.h"
#include "bit_utils.h"
#include "page_table.h"

#include <stdint.h>


static bool paging_enabled;
static uint32_t root_page_table = 0;
uint32_t* root_page_ptr = page_table_lv1_ptr;

void page_table_set_root_page(uint32_t table) {
    kprintf(K_DEBUG,
            "paging: setting root page table to %p table (old value=%p)\n",
            table, root_page_table);
    root_page_table = table;
    uint32_t old_satp = satp_r_csr();
    uint32_t ppn = table / FRAME_SIZE;
    // TODO: utilize ASID
    uint32_t new_satp = satp_set_ppn(old_satp, ppn);
    satp_w_csr(new_satp);
}

uint32_t sv32_pte(uint32_t paddr, bool user_access,
                  bool can_read, bool can_write,
                  bool can_exec, bool global,
                  bool valid, bool fixup) {
    uint32_t pte = (paddr >> 12U) << 10U;
    pte = sv32_set_user_can_access(pte, user_access);
    pte = sv32_set_can_execute(pte, can_exec);
    pte = sv32_set_can_write(pte, can_write);
    pte = sv32_set_can_read(pte, can_read);
    pte = sv32_set_is_global(pte, global);
    pte = sv32_set_valid(pte, valid);
    pte = sv32_set_rsw(pte, (fixup == true ? RSW_LV1_FIXUP : 0));
    return pte;
}

uint32_t sv32_user_pte(uint32_t paddr, bool can_read,
                       bool can_write, bool can_exec,
                       bool valid, bool fixup) {
    return sv32_pte(paddr, true, can_read,
                    can_write, can_exec, false, valid, fixup);
}

uint32_t sv32_kernel_pte(uint32_t paddr, bool can_read,
                         bool can_write, bool can_exec,
                         bool valid, bool fixup) {
    return sv32_pte(paddr, false, can_read,
                    can_write, can_exec, false, valid, fixup);
}

uint32_t sv32_kernel_pte_pointer(uint32_t paddr, bool valid) {
    return sv32_pte(paddr, false, false,
                    false, false, false, valid, false);
}

uint32_t sv32_user_pte_pointer(uint32_t paddr, bool valid) {
    return sv32_pte(paddr, true, false,
                    false, false, false, valid, false);
}