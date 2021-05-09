#include "kprint.h"
#include "constants.h"
#include "page_frame.h"
#include "simple_falloc.h"

int32_t stack_ptr = MAX_NR_FRAMES_SUPPORTED;
uint32_t frame_stack[MAX_NR_FRAMES_SUPPORTED];

uint32_t simple_falloc_alloc() {
    if (stack_ptr == MAX_NR_FRAMES_SUPPORTED) {
        kputs("simple_falloc [alloc]: frame pool is empty\n");
        return 0;
    }
    uint32_t next_frame = frame_stack[stack_ptr++];
    uint32_t frame_addr = next_frame * FRAME_SIZE;
    pf_bitmap_mark_allocated(next_frame);
    kprintf("simple_falloc [alloc]: "
            "returning frame %d (%p) from pool\n", frame_addr, next_frame);
    return next_frame;
}

void simple_falloc_free(uint32_t frame) {
    if (!pf_bitmap_bit_is_on(frame))
        return;
    if (stack_ptr == 0)
        return;
    uint32_t frame_addr = frame * FRAME_SIZE;
    kprintf("simple_falloc [free]: returning frame %d (%p) to the pool\n",
            frame, frame_addr);
    pf_bitmap_mark_free(frame);
    frame_stack[--stack_ptr] = frame;
}

void simple_falloc_add(uint32_t frame) {
    // used to boostrap the allocator
    if (stack_ptr == 0)
        return;
    uint32_t frame_addr = frame * FRAME_SIZE;
    kprintf("simple_falloc [add]: adding frame %d (%p) to the pool\n",
            frame, frame_addr);
    pf_bitmap_mark_free(frame);
    frame_stack[--stack_ptr] = frame;
}

uint32_t simple_falloc_free_count() {
    return MAX_NR_FRAMES_SUPPORTED - stack_ptr;
}

void simple_falloc_init_from_range(uint32_t base, uint32_t size) {
    uint32_t frame_base = base / FRAME_SIZE;
    uint32_t page_count = size / FRAME_SIZE;
    for (uint32_t i = 0, f = frame_base; i < page_count; i++,base++)
        simple_falloc_add(f);
}