#ifndef RISCV_MICROK_BUDDY_FALLOC_H
#define RISCV_MICROK_BUDDY_FALLOC_H
#include "devtree.h"

typedef struct {
    bool valid;
    uint32_t address;
    uint32_t order;
} BuddyAllocResult;

void buddy_free(uint32_t address, int32_t order);
        BuddyAllocResult buddy_allocate(int32_t order);
void buddy_process_memory_range(uint32_t base_addr, uint32_t region_size);
void buddy_init_from_dev_tree(DeviceTreeContext* ctx);
void buddy_init_from_range(uint32_t base_addr, uint32_t size);


#endif //RISCV_MICROK_BUDDY_FALLOC_H
