#ifndef RISCV_MICROK_PAGE_TABLE_H
#define RISCV_MICROK_PAGE_TABLE_H

#include "bit_utils.h"

#include <stdbool.h>

#define RSW_LV1_FIXUP 2
#define sv32_page_offset(addr) bits(addr, 0, 12)
// level 2
#define sv32_vpn0(addr) bits(addr, 12, 10)
// level 1
#define sv32_vpn1(addr) bits(addr, 22, 10)
#define sv32_is_valid(pte) (bits(pte, 0, 1) == 1 ? true : false)
#define sv32_can_read(pte) (bits(pte, 1, 1) == 1 ? true : false)
#define sv32_can_write(pte) (bits(pte, 2, 1) == 1 ? true : false)
#define sv32_can_execute(pte) (bits(pte, 3, 1) == 1 ? true : false)
#define sv32_user_can_access(pte) (bits(pte, 4, 1) == 1 ? true : false)
#define sv32_is_global(pte) (bits(pte, 5, 1) == 1 ? true : false)
#define sv32_accessed(pte) (bits(pte, 6, 1) == 1 ? true : false)
#define sv32_is_dirty(pte) (bits(pte, 7, 1) == 1 ? true : false)
#define sv32_is_leaf_page(pte) (bits(pte, 1, 3) > 0 ? true : false)
#define sv32_rsw(pte) (bits(pte, 8, 2))
// level 2
#define sv32_ppn0(pte) (bits(pte, 10, 10))
// level 1
#define sv32_ppn1(pte) (bits(pte, 20, 12))

// sets
#define sv32_set_valid(pte, v) set_bits(pte, (v == true ? 1 : 0), 0, 1)
#define sv32_set_can_read(pte, v) set_bits(pte, (v == true ? 1 : 0), 1, 1)
#define sv32_set_can_write(pte, v) set_bits(pte, (v == true ? 1 : 0), 2, 1)
#define sv32_set_can_execute(pte, v) set_bits(pte, (v == true ? 1 : 0), 3, 1)
#define sv32_set_user_can_access(pte, v) set_bits(pte, (v == true? 1 : 0), 4, 1)
#define sv32_set_is_global(pte, v) set_bits(pte, (v == true? 1 : 0), 5, 1)
#define sv32_set_accessed(pte, v) set_bits(pte, (v == true ? 1 : 0), 6, 1)
#define sv32_set_dirty(pte, v) set_bits(pte, (v == true? 1 : 0), 7, 1)
#define sv32_set_rsw(pte, v) set_bits(pte, v, 8, 2)
#define sv32_set_ppn0(pte, v) set_bits(pte, v, 10, 10)
#define sv32_set_ppn1(pte, v) set_bits(pte, v, 20, 12)

#define page_table_lv1_ptr ((uint32_t*)(1023 << 22 | 1022 << 12))
// this is used for modifying any physical page within the current
// address space by simply creating an entry and pointing to the page
#define page_table_lv1_spare_ptr ((uint32_t*)(1023 << 22 | 1021 << 12))
#define page_table_lv2_ptr(pde_index) ((uint32_t*)(1023 << 22 | pde_index << 12))

void page_table_simple_flush_tlb();
void page_table_set_root_page(uint32_t table);
uint32_t sv32_pte(uint32_t paddr, bool user_access,
                  bool can_read, bool can_write,
                  bool can_exec, bool global,
                  bool valid, bool fixup);
uint32_t sv32_user_pte(uint32_t paddr, bool can_read,
                       bool can_write, bool can_exec,
                       bool valid, bool fixup);
uint32_t sv32_kernel_pte(uint32_t paddr, bool can_read,
                         bool can_write, bool can_exec,
                         bool valid, bool fixup);
uint32_t sv32_kernel_pte_pointer(uint32_t paddr, bool valid);
uint32_t sv32_user_pte_pointer(uint32_t paddr, bool valid);


#endif //RISCV_MICROK_PAGE_TABLE_H
