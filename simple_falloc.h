#ifndef RISCV_MICROK_SIMPLE_FALLOC_H
#define RISCV_MICROK_SIMPLE_FALLOC_H

#include "page_frame.h"

uint32_t simple_falloc_alloc();
void simple_falloc_add(uint32_t frame);
void simple_falloc_free(uint32_t frame_addr);
uint32_t simple_falloc_free_count();
void simple_falloc_init_from_frame_bitmap();
void simple_falloc_init_from_range(uint32_t base, uint32_t size);

#endif //RISCV_MICROK_SIMPLE_FALLOC_H
