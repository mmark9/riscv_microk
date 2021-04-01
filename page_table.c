#include "csr.h"
#include "constants.h"
#include "bit_utils.h"
#include "page_table.h"

#include <stdint.h>

#define LVL1_SIZE 0x400000
#define PAGE_TABLE_NR_SLOTS 1024

static bool paging_enabled;
static uint32_t* page_table_current_lvl1;

bool paging_is_enabled() {
    return paging_enabled;
}

uint32_t* page_table_set_lvl1(uint32_t* frame) {
    uint32_t asid = 0;
    uint32_t ppn = (uint32_t)frame / PAGE_SIZE;
    uint32_t old_value = satp_r_csr();
    uint32_t new_value = set_bits(old_value, ppn, 0, 22);
    new_value = set_bits(old_value, asid, 22, 9);
    satp_w_csr(new_value);
    return (uint32_t*)old_value;
}

uint32_t* page_table_current_lvl1_page() {
    return page_table_current_lvl1;
}

uint32_t page_table_lvl1_entry(uint32_t address) {
    uint32_t pde_index = bits(address, 22, 10);
    uint32_t* pte_ptr = (uint32_t*)(1023 << 20 | 1023 << 10);
    return pte_ptr[pde_index];
}

// returns the old entry
uint32_t page_table_lvl1_set_entry(uint32_t pte, uint32_t address) {
    uint32_t pte_index = address / PAGE_SIZE;
    uint32_t* pte_ptr = (uint32_t*)(1023 << 20 | 1023 << 10);
    uint32_t old_entry = pte_ptr[pte_index];
    pte_ptr[pte_index] = pte;
    return old_entry;
}

uint32_t page_table_lvl2_entry(uint32_t address) {
    uint32_t pde_index = bits(address, 22, 10);
    uint32_t pte_index = bits(address, 12, 10);
    uint32_t* pte_ptr = (uint32_t*)(1023 << 20 | pde_index << 10);
    // TODO: panic() on invalid page entries
    return pte_ptr[pte_index];
}

// returns the old entry
uint32_t page_table_set_lvl2_entry(uint32_t pte, uint32_t address) {
    uint32_t pde_index = bits(address, 22, 10);
    uint32_t pte_index = bits(address, 12, 10);
    uint32_t* pte_ptr = (uint32_t*)(1023 << 20 | pde_index << 10);
    // TODO: panic() on invalid page entries
    uint32_t old_entry = pte_ptr[pte_index];
    pte_ptr[pte_index] = pte;
    return old_entry;
}

void page_table_simple_flush_tlb() {
    __asm__("sfence.vma zero, zero");
}

void page_table_init(uint32_t higher_half_addr, uint32_t kernel_start_addr,
                     uint32_t nr_direct_map_pgs, uint32_t* page_table) {
    // direct map direct_map_size to prevent page fault errors
    // TODO: panic()
    if (page_table == 0)
        return;
    // sort of redundant because paging will always be enabled
    paging_enabled = true;
    uint32_t hf_index = higher_half_addr / LVL1_SIZE;
    uint32_t phys_addr_ptr = kernel_start_addr;
    uint32_t last_index = hf_index + nr_direct_map_pgs;
    // TODO: panic()
    if (last_index >= PAGE_TABLE_NR_SLOTS)
        return;

    // TODO: use two level mapping for kernel area
    for (uint32_t i = 0, r=hf_index; i < nr_direct_map_pgs;
            i++,r++,phys_addr_ptr += PAGE_SIZE) {
        page_table[r] = phys_addr_ptr;
        page_table[r] = sv32_set_valid(page_table[r], true);
        page_table[r] = sv32_set_can_read(page_table[r], true);
        page_table[r] = sv32_set_can_execute(page_table[r], true);
        page_table[r] = sv32_set_user_can_access(page_table[r], false);
    }
    // set the last entry for recursive page table lookup
    page_table[1023] = 1023;
    page_table[1023] = sv32_set_valid(page_table[1023], true);
    page_table[1023] = sv32_set_can_read(page_table[1023], false);
    page_table[1023] = sv32_set_can_execute(page_table[1023], false);
    page_table[1023] = sv32_set_user_can_access(page_table[1023], false);
    page_table_set_lvl1(page_table);
    page_table_simple_flush_tlb();
    // report all okay
}



