#ifndef RISCV_MICROK_KHEAP_H
#define RISCV_MICROK_KHEAP_H
#include <stdint.h>
#include <stddef.h>

#include "arch.h"

void kheap_init(rvu_word heap_base, size_t size);
void* kheap_extend(rvu_word size);
rvu_word kheap_size();
rvu_word kheap_start();
rvu_word kheap_end();

#endif //RISCV_MICROK_KHEAP_H
