#ifndef RISCV_MICROK_KMALLOC_H
#define RISCV_MICROK_KMALLOC_H

void kfree(void* ptr);
void* kmalloc(uint32_t size);
int init_malloc(void* memory_start, uint32_t size);
#endif //RISCV_MICROK_KMALLOC_H
