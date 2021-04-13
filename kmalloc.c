#include "kheap.h"

#include <stdint.h>
#include <assert.h>

typedef union block_header {
    struct {
        unsigned int size;
        union block_header* next;
    } s;
    uint32_t x; // forces all header sizes to be a multiple of an int
} MallocHeader;

/**
 * unit size is in bytes
 * the underlying implementation will most likely
 * allocate memory in fixed size chunks so we
 */
#define BLOCK_UNIT_SIZE 16
#define BAD_ADDR 0xFFFFFFFF
#define HEADER_SIZE sizeof(MallocHeader)
#define MAX_INTERNAL_FRAGMENT_SIZE 16
#define HEAP_EXTEND_DEFAULT 4096

MallocHeader base_block;
MallocHeader* free_list = 0;


#define true 1
#define false 0

void kfree(void* ptr) {
    MallocHeader* free_block =
            (MallocHeader*)(ptr - sizeof(MallocHeader));
    MallocHeader* cur = free_list->s.next;
    MallocHeader* prev = free_list;
    if (ptr == 0)
        return;
    while(true) {
        // look for a spot to put this block
        if(cur == free_list) {
            // add this block to head of list
            // shouldn't happen normally
            // normally free is only called after at least one call to malloc
            cur->s.next = free_block;
            free_block->s.next = cur;
            break;
        } else if(cur > free_block) {
            if(((void*)free_block + free_block->s.size) == (void*)cur) {
                // join these two blocks
                free_block->s.size += cur->s.size;
                free_block->s.next = cur->s.next;
                // below is not necessary
                cur->s.next = 0;
                cur->s.size = 0;
            } else {
                // just link
                free_block->s.next = cur;
            }
            if(((void*)prev + prev->s.size) == (void*)free_block) {
                // join these two blocks
                prev->s.size += free_block->s.size;
                prev->s.next = free_block->s.next;
                // below is not necessary
                free_block->s.next = 0;
                free_block->s.size = 0;
            } else {
                prev->s.next = free_block;
            }
            break;
        } else if(cur == free_block) {
            // Double free detected
            // TODO: set errno or something to indicate an error
            break;
        } else {
            prev = cur;
            cur = cur->s.next;
        }
    }
}


void* kmalloc(unsigned int nr_bytes) {
    void* addr = 0;
    MallocHeader* cur = free_list->s.next;
    MallocHeader* prev = free_list;
    MallocHeader* temp;
    unsigned int true_size = nr_bytes + HEADER_SIZE;
    while(true) {
        if(cur == &base_block) {
            // no more memory available for heap
            // request more
            void* new_addr = kheap_extend(HEAP_EXTEND_DEFAULT);
            if (new_addr != 0)
                kfree(new_addr);
            else
                break;
        }
        int size_diff = cur->s.size - true_size;
        if(size_diff >= 0 && size_diff < MAX_INTERNAL_FRAGMENT_SIZE) {
            // no need to split this block up - good fit
            // remove this block from the free list
            prev->s.next = cur->s.next;
            cur->s.next = 0; // unlink this block
            addr = (void*)cur + HEADER_SIZE;
            break;
        }else if(size_diff > MAX_INTERNAL_FRAGMENT_SIZE) {
            // we should split this block up
            // to avoid too much internal fragmentation
            // first create the new block
            temp = (MallocHeader*)((void*)cur + true_size);
            temp->s.size = size_diff;
            // add the new block to the free list
            temp->s.next = cur->s.next;
            prev->s.next = temp;
            // unlink and finalize the returned block
            cur->s.next = 0;
            cur->s.size = true_size;
            addr = (void*)cur + HEADER_SIZE;
            break;
        } else {
            prev = cur;
            cur = cur->s.next;
        }
    }
    return addr;
}


int init_malloc(void* memory_start, unsigned int size_in_bytes) {
    if(size_in_bytes < 5) {
        return 1;
    }
    MallocHeader* big_block = (MallocHeader*)memory_start;
    big_block->s.size = size_in_bytes - HEADER_SIZE;
    void* target_addr = (void*)big_block + HEADER_SIZE;
    base_block.s.size = 0;
    base_block.s.next = (MallocHeader*)&base_block;
    free_list = (MallocHeader*)&base_block;
    kfree(target_addr);
    return 0;
}

