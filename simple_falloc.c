#include "kprint.h"
#include "system.h"
#include "constants.h"
#include "page_frame.h"
#include "simple_falloc.h"

int32_t stack_ptr = MAX_NR_FRAMES_SUPPORTED;
uint32_t frame_stack[MAX_NR_FRAMES_SUPPORTED];

uint32_t simple_falloc_alloc() {
    if (stack_ptr == MAX_NR_FRAMES_SUPPORTED) {
        kputs(K_DEBUG,
              "simple_falloc [alloc]: frame pool is empty\n");
        return 0;
    }
    uint32_t next_frame = frame_stack[stack_ptr++];
    uint32_t frame_addr = next_frame * FRAME_SIZE;
    pf_bitmap_mark_allocated(next_frame);
    kprintf(K_DEBUG,
            "simple_falloc [alloc]: "
            "returning frame %d (%p) from pool\n", next_frame, frame_addr);
    return frame_addr;
}

void simple_falloc_free(uint32_t frame_addr) {
    uint32_t frame_no = frame_addr / FRAME_SIZE;
    if (!pf_bitmap_bit_is_on(frame_no)) {
        kprintf(K_DEBUG,
                "simple_falloc [free]: "
                "frame_addr %u (%p) is already free\n", frame_no, frame_addr);
        return;
    }
    if (stack_ptr == 0) {
        kprintf(K_DEBUG,
                "simple_falloc [free]: cannot free "
                "frame_addr %u (%p); stack is full\n", frame_no, frame_addr);
        sys_panic("frame_addr allocation bug");
    }
    kprintf(K_DEBUG,
            "simple_falloc [free]: returning "
            "frame_addr %u (%p) to the pool\n",
            frame_no, frame_addr);
    pf_bitmap_mark_free(frame_no);
    frame_stack[--stack_ptr] = frame_no;
}

void simple_falloc_add(uint32_t frame) {
    // used to boostrap the allocator
    if (stack_ptr == 0) {
        kprintf(K_DEBUG,
                "simple_falloc [free]: cannot free frame %u; stack is full\n", frame);
        sys_panic("frame allocation bug");
    }
    /*uint32_t frame_addr = frame * FRAME_SIZE;
    kprintf("simple_falloc [add]: adding frame %u (%p) to the pool\n",
            frame, frame_addr);*/
    pf_bitmap_mark_free(frame);
    frame_stack[--stack_ptr] = frame;
}

uint32_t simple_falloc_free_count() {
    return MAX_NR_FRAMES_SUPPORTED - stack_ptr;
}


void simple_falloc_init_from_frame_bitmap(uint32_t mem_start,
                                          uint32_t mem_size) {
    uint32_t free_count = 0;
    uint32_t frame_start = mem_start / FRAME_SIZE;
    uint32_t num_frames = mem_size / FRAME_SIZE;
    stack_ptr = MAX_NR_FRAMES_SUPPORTED;
    for (uint32_t f = frame_start, i = 0; i < num_frames; i++,f++) {
        if (pf_bitmap_bit_is_on(f))
            continue;
        simple_falloc_add(f);
        free_count += 1;
    }
    kprintf(K_DEBUG, "falloc [init]: %u frames are available\n", free_count);
}

void simple_falloc_init_from_range(uint32_t base, uint32_t size) {
    uint32_t frame_base = base / FRAME_SIZE;
    uint32_t page_count = size / FRAME_SIZE;
    for (uint32_t i = 0, f = frame_base; i < page_count; i++,base++)
        simple_falloc_add(f);
}