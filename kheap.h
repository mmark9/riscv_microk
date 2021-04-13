#ifndef RISCV_MICROK_KHEAP_H
#define RISCV_MICROK_KHEAP_H
#include <stdint.h>

void kheap_init(uint32_t heap_base, uint32_t size);
void* kheap_extend(uint32_t size);
uint32_t kheap_size();
uint32_t kheap_start();
uint32_t kheap_end();

#endif //RISCV_MICROK_KHEAP_H
