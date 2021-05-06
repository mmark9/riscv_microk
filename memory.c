#include "memory.h"
#include "system.h"
#include "kprint.h"
#include "constants.h"
#include "page_table.h"
#include "buddy_falloc.h"

uint64_t memory_range_from_device_tree(const void* devtree) {
    DeviceTreeContext ctx;
    uint32_t res = devtree_load_context(devtree, &ctx);
    uint32_t node_count = devtree_child_node_count(&ctx);
    uint32_t word0, word1, word2, word3;
    word0 = word1 = word2 = word3 = 0;
    DeviceTreeProp prop;
    for (uint32_t i = 0; i < node_count; i++) {
        if (streq_node(devtree_child_name(i, &ctx), "memory")) {
            res = devtree_move_to_child(i, &ctx);
            res = devtree_property("reg", &prop, &ctx);
            res = devtree_word_at_index(0, &prop, &word0, &ctx);
            res = devtree_word_at_index(1, &prop, &word1, &ctx);
            res = devtree_word_at_index(2, &prop, &word2, &ctx);
            res = devtree_word_at_index(3, &prop, &word3, &ctx);
            break;
        }
    }
    uint64_t ret = word1;
    ret <<= 32LU;
    ret |= word3;
    return ret;
}



void setup_memory_subsystem(uint32_t load_addr,
                            uint32_t mem_base,
                            uint32_t mem_size,
                            uint32_t kernel_size) {
    uint32_t mem_end = mem_base + mem_size;
    uint32_t kernel_phys_end = load_addr + kernel_size;
    uint32_t frame_pool_start = kernel_phys_end;
    uint32_t frame_pool_size = mem_end - frame_pool_start;
    buddy_init_from_range(frame_pool_start, frame_pool_size);
}

void map_kernel_higher_half(uint32_t load_addr,
                            uint32_t hh_vaddr,
                            uint32_t kernel_size) {
    uint32_t new_pte = 0;
    uint32_t mb4 = 0x1U << 22U;
    uint32_t num_4mb_mappings = kernel_size >> 22U;
    uint32_t vaddr_ptr = hh_vaddr;
    uint32_t paddr_ptr = load_addr;
    uint32_t pde_index = sv32_vpn1(hh_vaddr);
    uint32_t* page_table_lv1 = page_table_lv1_ptr;
    uint32_t old_pte = page_table_lv1[pde_index];
    for (uint32_t i = 0, p = pde_index; i < num_4mb_mappings; i++,p++) {
        new_pte = sv32_kernel_pte(paddr_ptr, true,
                                  true, true, true);
        page_table_lv1[p] = new_pte;
        vaddr_ptr += mb4;
        paddr_ptr += mb4;
    }
    // tlb flush?
}



void map_device_tree_area(uint32_t device_tree_addr) {
    // for now we will just map the device tree area 1:1
    uint32_t* page_table_lv1 = page_table_lv1_ptr;
    uint32_t tree_pde_index = sv32_vpn1(device_tree_addr);
    uint32_t tree_aligned_addr = (device_tree_addr >> 22U) << 22U;
    uint32_t tree_pte = sv32_kernel_pte(tree_aligned_addr,
                                        true, false,
                                        false, true);
    page_table_lv1[tree_pde_index] = tree_pte;
}

void create_early_identity_map(uint32_t firmware_addr, uint32_t map_size) {
    uint32_t pte = 0;
    uint32_t mb4 = 0x1 << 22U;
    uint32_t num_mappings = map_size >> 22U;
    uint32_t pde_index = sv32_vpn1(firmware_addr);
    uint32_t aligned_addr = (firmware_addr >> 22U) << 22U;
    uint32_t* page_table_lv1 = page_table_lv1_ptr;
    for (uint32_t i = 0, p = pde_index; i < num_mappings; i++,p++) {
        pte = sv32_kernel_pte(aligned_addr,
                              true, true,
                              true, true);
        page_table_lv1[p] = pte;
        aligned_addr += mb4;
    }
    // tlb flush?
}

void setup_kernel_heap(uint32_t heap_base, uint32_t heap_size) {
    kheap_init(heap_base, heap_size);
    init_malloc((void*)kheap_start(), kheap_size());
}

typedef enum {
    TEXT_SEGMENT = 0,
    READ_ONLY_SEGMENT,
    DATA_SEGMENT,
    BSS_SEGMENT,
    HEAP_SEGMENT
} SegmentType;

void mem_placement_map_segment_low(uint32_t v_addr_base,
                                   uint32_t p_addr_base,
                                   uint32_t nr_pages,
                                   SegmentType seg_type) {
    // maps a segment which is a contiguous region
    // containing the same protection attributes
    // segments must start at a page boundary
    // Note: this function does not allocate second level pages
    uint32_t pde_index = 0;
    uint32_t frame_addr = 0;
    uint32_t pte_index = 0;
    BuddyAllocResult buddy_res;
    uint32_t v_addr_ptr = v_addr_base;
    uint32_t p_addr_ptr = p_addr_base;
    uint32_t* page_table_lv1 = page_table_lv1_ptr;
    uint32_t* page_table_lv2 = page_table_lv2_ptr(0);
    for (uint32_t i = 0; i < nr_pages; i++) {
        // check if we need to set a PDE
        pde_index = sv32_vpn1(v_addr_ptr);
        if (!sv32_is_valid(page_table_lv1[pde_index])
            || !sv32_is_leaf_page(page_table_lv1[pde_index])) {
            buddy_res = buddy_allocate(0);
            if (!buddy_res.valid)
                panic("mem: no available free frames available to map segment\n");
            kprintf("mem: mapping lv1 page (%p) to virtual address %p\n",
                    frame_addr, v_addr_ptr);
            page_table_lv1[pde_index] = sv32_kernel_pte_pointer(buddy_res.address, true);
        }
        pte_index = sv32_vpn0(v_addr_ptr);
        page_table_lv2 = page_table_lv2_ptr(pde_index);

        if (seg_type == TEXT_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(p_addr_ptr,
                                                        false,
                                                        false,
                                                        true,
                                                        true);
            kprintf("mem: mapping lv2 text page (%p) to virtual address (%p)\n",
                    p_addr_ptr, v_addr_ptr);
        } else if (seg_type == DATA_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(p_addr_ptr,
                                                        true,
                                                        true,
                                                        false,
                                                        true);
            kprintf("mem: mapping lv2 data page (%p) to virtual address (%p)\n",
                    p_addr_ptr, v_addr_ptr);
        } else if (seg_type == READ_ONLY_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(p_addr_ptr,
                                                        true,
                                                        false,
                                                        false,
                                                        true);
            kprintf("mem: mapping lv2 read-only page (%p) to virtual address (%p)\n",
                    p_addr_ptr, v_addr_ptr);
        } else if (seg_type == BSS_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(p_addr_ptr,
                                                        true,
                                                        true,
                                                        false,
                                                        true);
            kprintf("mem: mapping lv2 bss page (%p) to virtual address (%p)\n",
                    p_addr_ptr, v_addr_ptr);
        } else {
            panic("mem: mapping heap segment not supported yet");
        }
        v_addr_ptr += PAGE_SIZE;
        p_addr_ptr += PAGE_SIZE;
    }
}

void mem_placement_map_segment(uint32_t p_start,
                               uint32_t v_start,
                               uint32_t size,
                               SegmentType type) {
    uint32_t nr_pages_needed = size / FRAME_SIZE;
    uint32_t page_count_remain = size % FRAME_SIZE;
    nr_pages_needed = page_count_remain > 0 ? nr_pages_needed + 1 : nr_pages_needed;
    mem_placement_map_segment_low(v_start, p_start, nr_pages_needed, type);
}

uint32_t mem_size_in_pages(uint32_t bytes) {
    uint32_t num_pages = bytes / PAGE_SIZE;
    uint32_t num_pages_remain = bytes % PAGE_SIZE;
    num_pages = num_pages_remain > 0 ? num_pages + 1 : num_pages;
    return num_pages;
}

void mem_setup_page_table(KernelLinkerConfig* config) {
    // assume no second level pages exist
    // assume that we have a recursive PTE in the last of the page table
    // MAP TEXT SEGMENT
    uint32_t text_v_addr = config->kernel_virtual_base;
    uint32_t kernel_text_size = config->kernel_text_end - config->kernel_text_begin;
    mem_placement_map_segment(config->kernel_text_begin, text_v_addr, kernel_text_size, TEXT_SEGMENT);
    // MAP RO SEGMENT
    // TODO: verify that size is a multiple of frame size
    uint32_t ro_v_addr = text_v_addr + kernel_text_size;
    uint32_t kernel_ro_size = config->kernel_ro_data_end - config->kernel_ro_data_begin;
    mem_placement_map_segment(config->kernel_ro_data_begin, ro_v_addr, kernel_ro_size, READ_ONLY_SEGMENT);
    // MAP DATA SEGMENT
    // TODO: verify that size is a multiple of frame size
    uint32_t data_v_addr = ro_v_addr + kernel_ro_size;
    uint32_t kernel_data_size = config->kernel_ro_data_end - config->kernel_ro_data_begin;
    mem_placement_map_segment(config->kernel_data_begin, data_v_addr, kernel_data_size, DATA_SEGMENT);
    // MAP BSS SEGMENT
    // TODO: verify that size is a multiple of frame size
    uint32_t bss_v_addr = data_v_addr + kernel_data_size;
    uint32_t kernel_bss_size = config->kernel_bss_end - config->kernel_bss_begin;
    mem_placement_map_segment(config->kernel_data_begin, data_v_addr, kernel_data_size, DATA_SEGMENT);
    // TODO: map heap?
}