#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "arch.h"

static rvu_word heap_start = 0;
// marks the end of the heap
static rvu_word heap_end = 0;
static size_t heap_size = 0;
static bool heap_initialized = false;

void kheap_init(rvu_word heap_base, size_t size) {
    heap_size = size;
    heap_start = heap_base;
    heap_end = heap_base + heap_size;
    heap_initialized = true;
}

void* kheap_extend(size_t size) {
    // check for overflow
    if (!heap_initialized)
        return 0;
    if (size == UINT32_MAX)
        return 0;
    rvu_word next_end = heap_end + size;
    if (next_end <= heap_end)
        return 0;
    rvu_word addr = heap_end;
    heap_end += size;
    return (void*)addr;
}

size_t kheap_size() {
    return heap_size;
}

rvu_word kheap_start() {
    return heap_start;
}

rvu_word kheap_end() {
    return heap_end;
}

