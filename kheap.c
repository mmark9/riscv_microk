#include <stdint.h>
#include <stdbool.h>

static uint32_t heap_start = 0;
// marks the end of the heap
static uint32_t heap_end = 0;
static uint32_t heap_size = 0;
static bool heap_initialized = false;

void kheap_init(uint32_t heap_base, uint32_t size) {
    heap_size = size;
    heap_start = heap_base;
    heap_end = heap_base + heap_size;
    heap_initialized = true;
}

void* kheap_extend(uint32_t size) {
    // check for overflow
    if (!heap_initialized)
        return 0;
    if (size == UINT32_MAX)
        return 0;
    uint32_t next_end = heap_end + size;
    if (next_end <= heap_end)
        return 0;
    uint32_t addr = heap_end;
    heap_end += size;
    return (void*)addr;
}

uint32_t kheap_size() {
    return heap_size;
}

uint32_t kheap_start() {
    return heap_start;
}

uint32_t kheap_end() {
    return heap_end;
}

