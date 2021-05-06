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
    uint32_t kernel_virtual_base;
    uint32_t kernel_virtual_end;
    uint32_t kernel_size_in_bytes;
} KernelLinkerConfig;

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
#endif //RISCV_MICROK_MEMORY_H
