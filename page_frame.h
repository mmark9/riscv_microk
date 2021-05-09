#ifndef RISCV_MICROK_PAGE_FRAME_H
#define RISCV_MICROK_PAGE_FRAME_H

#ifndef KERNEL_MODULES_PAGE_FRAME_H
#define KERNEL_MODULES_PAGE_FRAME_H

#include "memory.h"

#include <stdint.h>
#include <stdbool.h>

#define FRAME_SIZE 4096

bool pf_bitmap_bit_is_on(uint32_t frame_no);
void pf_bitmap_mark_free(uint32_t frame_no);
void pf_bitmap_mark_allocated(uint32_t frame_no);
int pf_bitmap_mark_reserved_frames(const void* dtb);
int pf_bitmap_mark_free_frames(uint32_t address, uint32_t size);
void pf_bitmap_mark_region_allocated(uint32_t address, uint32_t nr_pages);
void pf_bitmap_mark_region_free(uint32_t address, uint32_t nr_pages);
bool pf_bitmap_region_is_free(uint32_t address, uint32_t nr_pages);
uint32_t pf_bitmap_alloc_frame();
int init_frame_bitmap(const void* dtb);
void init_frame_bitmap_from_linker_config(KernelLinkerConfig* config);
#endif //KERNEL_MODULES_PAGE_FRAME_H


#endif //RISCV_MICROK_PAGE_FRAME_H
