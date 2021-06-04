#include "kprint.h"
#include "devtree.h"
#include "bit_utils.h"
#include "page_frame.h"

#include <stdint.h>
#include <stdbool.h>

#define FRAME_BIT_MAP_ROWS 64
#define NUM_FRAMES 1048576
#define NUM_BIT_MAP_ROWS 32768
#define FRAMES_PER_ROW 32

// declare bitmap in data section
uint32_t frame_bitmap[NUM_BIT_MAP_ROWS];

bool pf_bitmap_bit_is_on(uint32_t frame_no) {
    uint32_t frame_row = frame_no / FRAMES_PER_ROW;
    uint32_t bit_index = frame_no % FRAMES_PER_ROW;
    uint8_t bit_val = (frame_bitmap[frame_row] >> bit_index) & 0x1;
    return bit_val == 0x1;
}

void pf_bitmap_mark_free(uint32_t frame_no) {
    uint32_t frame_row = frame_no / FRAMES_PER_ROW;
    uint32_t bit_index = frame_no % FRAMES_PER_ROW;
    uint32_t word_mask = ~(0x1 << bit_index);
    frame_bitmap[frame_row] &= word_mask;
}

void pf_bitmap_mark_allocated(uint32_t frame_no) {
    uint32_t frame_row = frame_no / FRAMES_PER_ROW;
    uint32_t bit_index = frame_no % FRAMES_PER_ROW;
    uint32_t word_mask = 0x1 << bit_index;
    frame_bitmap[frame_row] |= word_mask;
}

int pf_bitmap_mark_region_by_memory_reserved(const DeviceTreeMemReserve* entry) {
    // assume 32-bit data-width for the memory bus
    uint32_t num_frames = entry->size / FRAME_SIZE;
    if (num_frames == 0)
        return -1;
    uint32_t pfn = 0;
    uint32_t address = (uint32_t)entry->address;
    pfn = bits(address, 12, 20);
    for (uint32_t i = 0; i < num_frames; i++) {
        pf_bitmap_mark_allocated(pfn);
        pfn++;
    }
    return 0;
}

int pf_bitmap_mark_reserved_frames(const void* dtb) {
    DeviceTreeContext ctx;
    int res = devtree_load_context(dtb, &ctx);
    if (res < 0)
        return -1;
    uint32_t res_count = 0;
    res = devtree_memory_reservation_count(&ctx);
    if (res < 0)
        return -2;
    DeviceTreeMemReserve res_entry;
    for (uint32_t i = 0; i < res_count; i++) {
        res = devtree_memory_reservation(i, &res_entry, &ctx);
        if (res < 0)
            return -3;
        res = pf_bitmap_mark_region_by_memory_reserved(&res_entry);
        if (res < 0)
            return -4;
    }
    return 0;
}

int pf_bitmap_mark_free_frames(uint32_t address, uint32_t size) {
    uint32_t num_frames = size / FRAME_SIZE;
    if (num_frames == 0)
        return -1;
    uint32_t pfn = bits(address, 12, 20);
    int32_t free_frame_count = 0;
    for (uint32_t i = 0; i < num_frames; i++) {
        pf_bitmap_mark_free(pfn);
        free_frame_count += 1;
    }
    return free_frame_count;
}

void pf_bitmap_mark_region_allocated(uint32_t address, uint32_t nr_pages) {
    uint32_t addr_ptr = address;
    for (uint32_t i = 0; i < nr_pages; i++) {
        pf_bitmap_mark_allocated(bits(addr_ptr, 12, 20));
        addr_ptr += FRAME_SIZE;
    }
}

void pf_bitmap_mark_region_free(uint32_t address, uint32_t nr_pages) {
    uint32_t addr_ptr = address;
    for (uint32_t i = 0; i < nr_pages; i++) {
        pf_bitmap_mark_free(bits(addr_ptr, 12, 20));
        addr_ptr += FRAME_SIZE;
    }
}

bool pf_bitmap_region_is_free(uint32_t address, uint32_t nr_pages) {
    uint32_t addr_ptr = address;
    for (uint32_t i = 0; i < nr_pages; i++) {
        if (pf_bitmap_bit_is_on(bits(addr_ptr, 12, 20)))
            return false;
        addr_ptr += FRAME_SIZE;
    }
    return true;
}

void init_frame_bitmap_from_linker_config(KernelLinkerConfig* config) {
    // this includes the deadzone below the firmware
    uint32_t total_image_size = config->kernel_bss_end;
    uint32_t total_image_frame_count = total_image_size / FRAME_SIZE;
    uint32_t total_remains = total_image_size % FRAME_SIZE;
    total_image_frame_count = total_remains > 1 ?
            total_image_frame_count + 1 : total_image_frame_count;
    pf_bitmap_mark_region_allocated(0, total_image_frame_count);
}

uint32_t pf_bitmap_alloc_frame() {
    uint32_t frame_no = 0;
    for (uint32_t i = 0; i < NUM_FRAMES; i++) {
        if (!pf_bitmap_bit_is_on(i)) {
            frame_no = i;
            break;
        }
    }
    if (frame_no == 0) {
        kputs(K_DEBUG,
              "page_frame [alloc]: no free frames available\n");
        return 0;
    }
    uint32_t frame_addr = frame_no * FRAME_SIZE;
    kprintf(K_DEBUG,
            "page_frame [alloc]: allocating frame %d (%p) from pool\n",
            frame_no, frame_addr);
    pf_bitmap_mark_allocated(frame_no);
    return frame_addr;
}

int init_frame_bitmap(const void* dtb) {
    DeviceTreeContext ctx;
    int res = devtree_load_context(dtb, &ctx);
    if (res < 0)
        return -1;
    int32_t free_frame_count = 0;
    uint32_t node_count = devtree_child_node_count(&ctx);
    uint32_t address = 0;
    uint32_t size = 0;
    DeviceTreeProp prop;
    for (uint32_t i = 0; i < node_count; i++) {
        if (streq_node(devtree_child_name(i, &ctx), "memory")) {
            res = devtree_property("reg", &prop, &ctx);
            res = devtree_word_at_index(0, &prop, &address, &ctx);
            res = devtree_word_at_index(1, &prop, &size, &ctx);
            free_frame_count += pf_bitmap_mark_free_frames(address, size);
        }
    }
    res = pf_bitmap_mark_reserved_frames(dtb);
    return free_frame_count;
}
