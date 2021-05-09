#ifndef RISCV_MICROK_MEMORY_H
#define RISCV_MICROK_MEMORY_H

#include <stdint.h>

typedef struct {
    uint32_t firmware_load_address;
    uint32_t kernel_load_address;
    uint32_t kernel_text_begin;
    uint32_t kernel_text_end;
    uint32_t kernel_ro_data_begin;
    uint32_t kernel_ro_data_end;
    uint32_t kernel_data_begin;
    uint32_t kernel_data_end;
    uint32_t kernel_bss_begin;
    uint32_t kernel_bss_end;
    uint32_t kernel_text_begin_virtual;
    uint32_t kernel_text_end_virtual;
    uint32_t kernel_ro_data_begin_virtual;
    uint32_t kernel_ro_data_end_virtual;
    uint32_t kernel_data_begin_virtual;
    uint32_t kernel_data_end_virtual;
    uint32_t kernel_bss_begin_virtual;
    uint32_t kernel_bss_end_virtual;
    uint32_t kernel_virtual_base;
    uint32_t kernel_virtual_end;
    uint32_t kernel_size_in_bytes;
} KernelLinkerConfig;

typedef enum {
    TEXT_SEGMENT = 0,
    READ_ONLY_SEGMENT,
    DATA_SEGMENT,
    BSS_SEGMENT,
    HEAP_SEGMENT
} SegmentType;

uint64_t memory_range_from_device_tree(const void* devtree);
void setup_memory_subsystem(uint32_t load_addr,
                            uint32_t mem_base,
                            uint32_t mem_size,
                            uint32_t kernel_size);
void map_kernel_higher_half(uint32_t load_addr,
                            uint32_t hh_vaddr,
                            uint32_t kernel_size);
void map_device_tree_area(uint32_t device_tree_addr);
void create_early_identity_map(uint32_t firmware_addr, uint32_t map_size);
void setup_kernel_heap(uint32_t heap_base, uint32_t heap_size);
void mem_setup_page_table(KernelLinkerConfig* config);
void mem_map_leaf_page(uint32_t phys_addr, uint32_t vaddr, SegmentType seg_type);
void mem_unmap_leaf_page(uint32_t vaddr);
#endif //RISCV_MICROK_MEMORY_H
