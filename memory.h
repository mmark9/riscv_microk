#ifndef RISCV_MICROK_MEMORY_H
#define RISCV_MICROK_MEMORY_H

#include "arch.h"
#include <stdint.h>
#include <stddef.h>

typedef struct {
    rvu_word firmware_load_address;
    rvu_word kernel_load_address;
    rvu_word kernel_text_begin;
    rvu_word kernel_text_end;
    rvu_word kernel_ro_data_begin;
    rvu_word kernel_ro_data_end;
    rvu_word kernel_data_begin;
    rvu_word kernel_data_end;
    rvu_word kernel_bss_begin;
    rvu_word kernel_bss_end;
    rvu_word kernel_text_begin_virtual;
    rvu_word kernel_text_end_virtual;
    rvu_word kernel_ro_data_begin_virtual;
    rvu_word kernel_ro_data_end_virtual;
    rvu_word kernel_data_begin_virtual;
    rvu_word kernel_data_end_virtual;
    rvu_word kernel_bss_begin_virtual;
    rvu_word kernel_bss_end_virtual;
    rvu_word kernel_virtual_base;
    rvu_word kernel_virtual_end;
    rvu_word kernel_size_in_bytes;
} KernelLinkerConfig;

typedef enum {
    TEXT_SEGMENT = 0,
    READ_ONLY_SEGMENT,
    DATA_SEGMENT,
    BSS_SEGMENT,
    HEAP_SEGMENT
} SegmentType;

uint64_t memory_range_from_device_tree(const void* devtree);
void setup_memory_subsystem(rvu_word load_addr,
                            rvu_word mem_base,
                            rvu_word mem_size,
                            rvu_word kernel_size);
void map_kernel_higher_half(rvu_word load_addr,
                            rvu_word hh_vaddr,
                            rvu_word kernel_size);
void map_device_tree_area(rvu_word device_tree_addr);
void create_early_identity_map(rvu_word firmware_addr, rvu_word map_size);
void setup_kernel_heap(rvu_word heap_base, size_t heap_size);
void mem_setup_page_table(KernelLinkerConfig* config);
void mem_map_leaf_page(rvu_word phys_addr, rvu_word vaddr, SegmentType seg_type);
void mem_unmap_leaf_page(rvu_word vaddr);
void mem_set_kernel_virtual_start_address(rvu_word vbase);
void mem_clone_kernel_address_space(rvu_word page);
#endif //RISCV_MICROK_MEMORY_H
