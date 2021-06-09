#ifndef RISCV_MICROK_KMALLOC_H
#define RISCV_MICROK_KMALLOC_H

#include <stddef.h>

void kfree(void* ptr);
void* kmalloc(size_t size);
int init_malloc(void* memory_start, size_t size);
#endif //RISCV_MICROK_KMALLOC_H
