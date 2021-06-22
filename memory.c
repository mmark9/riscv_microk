#include "utils.h"
#include "memory.h"
#include "system.h"
#include "kprint.h"
#include "devtree.h"
#include "constants.h"
#include "page_table.h"
#include "page_frame.h"

// need to remember where the first entry
// begins for cloning purposes
// Zero is always assumed to be invalid
uint32_t kernel_virtual_start_index = 0;

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

void setup_memory_subsystem(rvu_word load_addr,
                            rvu_word mem_base,
                            rvu_word mem_size,
                            rvu_word kernel_size) {
    uint32_t mem_end = mem_base + mem_size;
    uint32_t kernel_phys_end = load_addr + kernel_size;
    uint32_t frame_pool_start = kernel_phys_end;
    frame_pool_start = (frame_pool_start >> 12) << 12;
    uint32_t frame_pool_size = mem_end - frame_pool_start;
}

void mem_do_page_table_fixup() {
    uint32_t fixup_pte = 0;
    uint32_t address = 0;
    uint32_t* page_table_lv1 = page_table_lv1_ptr;
    for (uint32_t i = 0; i < PAGE_TABLE_NR_SLOTS; i++) {
        if (sv32_rsw(page_table_lv1[i]) == RSW_LV1_FIXUP) {
            // convert this to a pointer
            address = (page_table_lv1[i] >> 10) << 12;
            fixup_pte = sv32_kernel_pte_pointer(address, true);
            page_table_lv1[i] = fixup_pte;
        }
    }
}


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
    uint32_t v_addr_ptr = v_addr_base;
    uint32_t p_addr_ptr = p_addr_base;
    uint32_t* page_table_lv1 = page_table_lv1_ptr;
    uint32_t* page_table_lv2 = page_table_lv2_ptr(0);
    for (uint32_t i = 0; i < nr_pages; i++) {
        // check if we need to set a PDE
        pde_index = sv32_vpn1(v_addr_ptr);
        if (!sv32_is_valid(page_table_lv1[pde_index])
            || !sv32_is_leaf_page(page_table_lv1[pde_index])) {
            frame_addr = pf_bitmap_alloc_frame();
            if (frame_addr == 0)
                sys_panic("mem: no available free frames available to map segment\n");
            kprintf(K_DEBUG,
                    "mem: mapping lv1 page (%p) to virtual address %p\n",
                    frame_addr, v_addr_ptr);
            page_table_lv1[pde_index] = sv32_kernel_pte(frame_addr,
                                                        true, true,
                                                        false, true, true);
        }
        pte_index = sv32_vpn0(v_addr_ptr);
        page_table_lv2 = page_table_lv2_ptr(pde_index);
        if (seg_type == TEXT_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(p_addr_ptr,
                                                        false,
                                                        false,
                                                        true,
                                                        true,
                                                        false);
            kprintf(K_DEBUG,
                    "mem: mapping lv2 text page (%p) to virtual address (%p)\n",
                    p_addr_ptr, v_addr_ptr);
        } else if (seg_type == DATA_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(p_addr_ptr,
                                                        true,
                                                        true,
                                                        false,
                                                        true,
                                                        false);
            kprintf(K_DEBUG,
                    "mem: mapping lv2 data page (%p) to virtual address (%p)\n",
                    p_addr_ptr, v_addr_ptr);
        } else if (seg_type == READ_ONLY_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(p_addr_ptr,
                                                        true,
                                                        false,
                                                        false,
                                                        true,
                                                        false);
            kprintf(K_DEBUG,
                    "mem: mapping lv2 read-only page (%p) to virtual address (%p)\n",
                    p_addr_ptr, v_addr_ptr);
        } else if (seg_type == BSS_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(p_addr_ptr,
                                                        true,
                                                        true,
                                                        false,
                                                        true,
                                                        false);
            kprintf(K_DEBUG,
                    "mem: mapping lv2 bss page (%p) to virtual address (%p)\n",
                    p_addr_ptr, v_addr_ptr);
        } else {
            sys_panic("mem: mapping heap segment not supported yet");
        }
        v_addr_ptr += PAGE_SIZE;
        p_addr_ptr += PAGE_SIZE;
    }
    mem_do_page_table_fixup();
}

#define SV39_LV0_SIZE 2097152
#define SV39_LV1_SIZE 1073741824

uint64_t mem_sv39_l2_pte(uint64_t vaddr) {
    uint32_t l2_index = sv39_vpn2(vaddr);
    uint64_t* l2_ptr = page_table_sv39_lv2_ptr;
    return l2_ptr[l2_index];
}

uint64_t mem_sv39_l1_pte(uint64_t vaddr ) {
    uint32_t l2_index = sv39_vpn2(vaddr);
    uint32_t l1_index = sv39_vpn1(vaddr);
    uint64_t* l2_ptr = page_table_sv39_lv2_ptr;
    sys_kassert(l2_index < 512 && l1_index < 512);
    uint64_t pte = l2_ptr[l2_index];
    uint32_t ppn = sv39_pte_ppn(pte);
    uint32_t frame_addr = ppn * FRAME_SIZE;
    uint64_t temp_pte = sv39_kernel_pte(frame_addr, true,
                                        true, false,
                                        true, false);
    l2_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = temp_pte;
    sys_tlb_flush_all();
    uint64_t* spare_ptr = page_table_sv39_lv2_spare1_ptr;
    uint64_t l1_pte = spare_ptr[l1_index];
    l2_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = 0;
    sys_tlb_flush_all();
    return l1_pte;
}

uint64_t mem_sv39_l0_pte(uint64_t vaddr) {
    uint32_t l2_index = sv39_vpn2(vaddr);
    uint32_t l1_index = sv39_vpn1(vaddr);
    uint32_t l0_index = sv39_vpn0(vaddr);
    uint64_t* l2_ptr = page_table_sv39_lv2_ptr;
    sys_kassert(l2_index < 512 && l1_index < 512 && l0_index < 512);
    uint64_t l2_pte = l2_ptr[l2_index];
    uint32_t l1_ppn = sv39_pte_ppn(l2_pte);
    uint32_t l1_frame_addr = l1_ppn * FRAME_SIZE;
    uint64_t l1_temp_pte = sv39_kernel_pte(l1_frame_addr, true,
                                           true, false,
                                           true, false);
    l2_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = l1_temp_pte;
    sys_tlb_flush_all();
    uint64_t* l1_spare_ptr = page_table_sv39_lv2_spare1_ptr;
    bool l1_is_valid = sv39_is_valid(l1_spare_ptr[l1_index]);
    if (!l1_is_valid)
        return false;
    uint64_t l1_pte = l1_spare_ptr[l1_index];
    uint64_t l0_ppn = sv39_pte_ppn(l1_pte);
    uint32_t l0_frame_addr = l0_ppn * FRAME_SIZE;
    uint64_t l0_temp_pte = sv39_kernel_pte(l0_frame_addr,
                                           true, true,
                                           false, true, false);
    l2_ptr[ROOT_PAGE_TABLE_SPARE2_INDEX] = l0_temp_pte;
    sys_tlb_flush_all();
    uint64_t* l0_ptr = page_table_sv39_lv2_spare2_ptr;
    uint64_t l0_pte = l0_ptr[l0_index];
    // clean up l2 table
    l2_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = 0;
    l2_ptr[ROOT_PAGE_TABLE_SPARE2_INDEX] = 0;
    sys_tlb_flush_all();
    return l0_pte;
}

void mem_map_segment_low(uint32_t v_addr_base,
                         uint32_t nr_pages,
                         SegmentType seg_type) {
    // maps a segment which is a contiguous region
    // containing the same protection attributes
    // segments must start at a page boundary
    uint32_t pde_index = 0;
    uint32_t frame_addr = 0;
    uint32_t pte_index = 0;
    uint32_t v_addr_ptr = v_addr_base;
    uint32_t* page_table_lv1 = page_table_lv1_ptr;
    uint32_t* page_table_lv2 = page_table_lv2_ptr(0);
    for (uint32_t i = 0; i < nr_pages; i++) {
        // check if we need to set a PDE
        pde_index = sv32_vpn1(v_addr_ptr);
        if (!sv32_is_valid(page_table_lv1[pde_index])
            || !sv32_is_leaf_page(page_table_lv1[pde_index])) {
            frame_addr = pf_bitmap_alloc_frame();
            if (frame_addr == 0)
                sys_panic("mem: no available free frames available to map segment\n");
            kprintf(K_DEBUG,
                    "mem: mapping lv1 page (%p) to virtual address %p\n",
                    frame_addr, v_addr_ptr);
            // we temporarily map this as a leaf page for reverse mapping
            page_table_lv1[pde_index] = sv32_kernel_pte(frame_addr, true,
                                                        true, false, true,true);
        }
        pte_index = sv32_vpn0(v_addr_ptr);
        page_table_lv2 = page_table_lv2_ptr(pde_index);
        frame_addr = pf_bitmap_alloc_frame();
        if (frame_addr == 0)
            sys_panic("mem: failed to allocated more pages for segment map");
        if (seg_type == TEXT_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(frame_addr,
                                                        false,
                                                        false,
                                                        true,
                                                        true,
                                                        false);
            kprintf(K_DEBUG,
                    "mem: mapping lv2 text page (%p) to virtual address (%p)\n",
                    frame_addr, v_addr_ptr);
        } else if (seg_type == DATA_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(frame_addr,
                                                        true,
                                                        true,
                                                        false,
                                                        true,
                                                        false);
            kprintf(K_DEBUG,
                    "mem: mapping lv2 data page (%p) to virtual address (%p)\n",
                    frame_addr, v_addr_ptr);
        } else if (seg_type == READ_ONLY_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(frame_addr,
                                                        true,
                                                        false,
                                                        false,
                                                        true,
                                                        false);
            kprintf(K_DEBUG,
                    "mem: mapping lv2 read-only page (%p) to virtual address (%p)\n",
                    frame_addr, v_addr_ptr);
        } else if (seg_type == BSS_SEGMENT) {
            page_table_lv2[pte_index] = sv32_kernel_pte(frame_addr,
                                                        true,
                                                        true,
                                                        false,
                                                        true,
                                                        false);
            kprintf(K_DEBUG,
                    "mem: mapping lv2 bss page (%p) to virtual address (%p)\n",
                    frame_addr, v_addr_ptr);
        } else {
            sys_panic("mem: mapping heap segment not supported yet");
        }
        v_addr_ptr += PAGE_SIZE;
    }
    mem_do_page_table_fixup();
}

void mem_map_segment_sv39_lv0(uint32_t lv0_frame_addr, uint32_t* v_addr_ptr, uint32_t* nr_pages, SegmentType seg_type) {
    uint32_t pte_index = sv39_vpn0(*v_addr_ptr);
    uint32_t l0_slots_remain = 512 - pte_index;
    uint32_t map_count = min(l0_slots_remain, *nr_pages);
    *nr_pages -= map_count;
    uint64_t* lv2_ptr = page_table_sv39_lv2_ptr;
    lv2_ptr[ROOT_PAGE_TABLE_SPARE2_INDEX] = sv39_kernel_pte(lv0_frame_addr,
                                                            true, true,
                                                            false, true, false);
    sys_tlb_flush_all();
    uint64_t* spare_ptr = page_table_sv39_lv2_spare2_ptr;
    uint32_t frame_addr  = 0;
    for (uint32_t i = 0; i < map_count; i++) {
        pte_index = sv39_vpn0(*v_addr_ptr);
        frame_addr = pf_bitmap_alloc_frame();
        sys_kassert(frame_addr != 0);
        if (seg_type == TEXT_SEGMENT) {
            spare_ptr[pte_index] = sv39_kernel_pte(frame_addr,
                                                   false,
                                                   false,
                                                   true,
                                                   true,
                                                   false);
            kprintf(K_DEBUG,
                    "mem: mapping lv0 text page (%p) to virtual address (%p)\n",
                    frame_addr, *v_addr_ptr);
        } else if (seg_type == DATA_SEGMENT) {
            spare_ptr[pte_index] = sv39_kernel_pte(frame_addr,
                                                   true,
                                                   true,
                                                   false,
                                                   true,
                                                   false);
            kprintf(K_DEBUG,
                    "mem: mapping lv0 data page (%p) to virtual address (%p)\n",
                    frame_addr, *v_addr_ptr);
        } else if (seg_type == READ_ONLY_SEGMENT) {
            spare_ptr[pte_index] = sv39_kernel_pte(frame_addr,
                                                   true,
                                                   false,
                                                   false,
                                                   true,
                                                   false);
            kprintf(K_DEBUG,
                    "mem: mapping lv0 read-only page (%p) to virtual address (%p)\n",
                    frame_addr, v_addr_ptr);
        } else if (seg_type == BSS_SEGMENT) {
            spare_ptr[pte_index] = sv39_kernel_pte(frame_addr,
                                                   true,
                                                   true,
                                                   false,
                                                   true,
                                                   false);
            kprintf(K_DEBUG,
                    "mem: mapping lv0 bss page (%p) to virtual address (%p)\n",
                    frame_addr, *v_addr_ptr);
        } else {
            sys_panic("mem: mapping heap segment not supported yet");
        }
        *v_addr_ptr += PAGE_SIZE;
    }
}

void mem_map_segment_sv39_lv1(uint32_t l1_frame_addr,
                                           uint32_t v_addr,
                                           uint32_t map_size,
                                           SegmentType seg_type) {
    uint32_t l1_index = 0;
    // L0 table map count
    uint32_t nr_l0_maps = map_size / SV39_LV0_SIZE;
    uint32_t nr_l0_maps_remain = map_size % SV39_LV0_SIZE;
    nr_l0_maps = nr_l0_maps_remain > 0 ? nr_l0_maps + 1 : nr_l0_maps;
    sys_kassert((l1_index + nr_l0_maps) < 512);
    // we can only map one segment at a time using spares
    uint64_t l0_frame_addr = 0;
    uint32_t v_addr_ptr = v_addr;
    uint32_t nr_ptes = map_size / FRAME_SIZE;
    uint32_t nr_ptes_remain = map_size % FRAME_SIZE;
    nr_ptes = nr_ptes_remain > 0 ? nr_ptes + 1 : nr_ptes;
    uint32_t l0_slots_remaining = 0;
    uint64_t* lv2_ptr = page_table_sv39_lv2_ptr;
    uint64_t* spare_ptr = page_table_sv39_lv2_spare1_ptr;
    lv2_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = sv39_kernel_pte(l1_frame_addr,
                                                           true, true,
                                                           false, true,
                                                           false);
    sys_tlb_flush_all();
    for (uint32_t c = 0; c < nr_l0_maps; c++) {
        l1_index = sv39_vpn1(v_addr_ptr);
        if (!sv39_is_valid(spare_ptr[l1_index])) {
            l0_frame_addr = pf_bitmap_alloc_frame();
            spare_ptr[l1_index] = sv39_kernel_pte_pointer(l0_frame_addr, true);
        } else {
            l0_frame_addr = sv39_pte_ppn(spare_ptr[l1_index]) * FRAME_SIZE;
        }
        sys_kassert(l0_frame_addr != 0);
        mem_map_segment_sv39_lv0(l0_frame_addr, &v_addr_ptr,
                                           &nr_ptes, seg_type);
    }
    lv2_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = 0;
}

void setup_kernel_heap(rvu_word heap_base, size_t heap_size) {
    kheap_init(heap_base, heap_size);
#ifdef RV64
    uint64_t l2_pte = mem_sv39_l2_pte(heap_base);
    sys_kassert(sv39_is_valid(l2_pte));
    uint32_t l1_frame_addr = sv39_pte_ppn(l2_pte) * FRAME_SIZE;
    mem_map_segment_sv39_lv1(l1_frame_addr, heap_base, heap_size, DATA_SEGMENT);
#else
    rvu_word pages_needed = heap_size / FRAME_SIZE;
    rvu_word size_remain = heap_size % FRAME_SIZE;
    if (size_remain > 0)
        pages_needed += 1;
    mem_map_segment_low(heap_base, pages_needed, DATA_SEGMENT);
#endif
    init_malloc((void*)kheap_start(), kheap_size());
}

void mem_placement_map_segment(uint32_t p_start,
                               uint32_t v_start,
                               uint32_t size,
                               SegmentType type) {
    uint32_t nr_pages_needed = size / FRAME_SIZE;
    uint32_t page_count_remain = size % FRAME_SIZE;
    nr_pages_needed = page_count_remain > 0 ? nr_pages_needed + 1 : nr_pages_needed;
    kprintf(K_DEBUG,
            "mem: creating %u mappings for segment type %d\n", nr_pages_needed, type);
    mem_placement_map_segment_low(v_start, p_start, nr_pages_needed, type);
}

void mem_placement_map_segment_sv39_lv0(uint32_t l0_frame_addr, uint32_t* v_addr_ptr,
                                        uint32_t* p_addr_ptr, uint32_t* nr_pages,
                                        SegmentType seg_type) {
    uint32_t pte_index = sv39_vpn0(*v_addr_ptr);
    uint32_t l0_slots_remain = 512 - pte_index;
    uint32_t map_count = min(l0_slots_remain, *nr_pages);
    *nr_pages -= map_count;
    uint64_t* lv2_ptr = page_table_sv39_lv2_ptr;
    lv2_ptr[ROOT_PAGE_TABLE_SPARE2_INDEX] = sv39_kernel_pte(l0_frame_addr,
                                                            true, true,
                                                            false, true, false);
    sys_tlb_flush_all();
    uint64_t* spare_ptr = page_table_sv39_lv2_spare2_ptr;
    for (uint32_t i = 0; i < map_count; i++) {
        pte_index = sv39_vpn0(*v_addr_ptr);
        if (seg_type == TEXT_SEGMENT) {
            spare_ptr[pte_index] = sv39_kernel_pte(*p_addr_ptr,
                                                   true,
                                                   false,
                                                   true,
                                                   true,
                                                   false);
            kprintf(K_DEBUG,
                    "mem: mapping lv0 text page (%p) to virtual address (%p)\n",
                    *p_addr_ptr, *v_addr_ptr);
        } else if (seg_type == DATA_SEGMENT) {
            spare_ptr[pte_index] = sv39_kernel_pte(*p_addr_ptr,
                                                   true,
                                                   true,
                                                   false,
                                                   true,
                                                   false);
            kprintf(K_DEBUG,
                    "mem: mapping lv0 data page (%p) to virtual address (%p)\n",
                    *p_addr_ptr, *v_addr_ptr);
        } else if (seg_type == READ_ONLY_SEGMENT) {
            spare_ptr[pte_index] = sv39_kernel_pte(*p_addr_ptr,
                                                   true,
                                                   false,
                                                   false,
                                                   true,
                                                   false);
            kprintf(K_DEBUG,
                    "mem: mapping lv0 read-only page (%p) to virtual address (%p)\n",
                    *p_addr_ptr, *v_addr_ptr);
        } else if (seg_type == BSS_SEGMENT) {
            spare_ptr[pte_index] = sv39_kernel_pte(*p_addr_ptr,
                                                   true,
                                                   true,
                                                   false,
                                                   true,
                                                   false);
            kprintf(K_DEBUG,
                    "mem: mapping lv0 bss page (%p) to virtual address (%p)\n",
                    *p_addr_ptr, *v_addr_ptr);
        } else {
            sys_panic("mem: mapping heap segment not supported yet");
        }
        *v_addr_ptr += PAGE_SIZE;
        *p_addr_ptr += PAGE_SIZE;
    }
}


void mem_placement_map_hh_segment_sv39_lv1(uint32_t l1_frame_addr,
                                           uint32_t p_addr, uint32_t v_addr,
                                           uint32_t map_size, SegmentType seg_type) {
    uint32_t l1_index = 0;
    // L0 table map count
    uint32_t nr_l0_maps = map_size / SV39_LV0_SIZE;
    uint32_t nr_l0_maps_remain = map_size % SV39_LV0_SIZE;
    nr_l0_maps = nr_l0_maps_remain > 0 ? nr_l0_maps + 1 : nr_l0_maps;
    sys_kassert((l1_index + nr_l0_maps) < 512);
    // we can only map one segment at a time using spares
    uint64_t l0_frame_addr = 0;
    uint32_t p_addr_ptr = p_addr;
    uint32_t v_addr_ptr = v_addr;
    uint32_t nr_ptes = map_size / FRAME_SIZE;
    uint32_t nr_ptes_remain = map_size % FRAME_SIZE;
    nr_ptes = nr_ptes_remain > 0 ? nr_ptes + 1 : nr_ptes;
    uint64_t* lv2_ptr = page_table_sv39_lv2_ptr;
    uint64_t* spare_ptr = page_table_sv39_lv2_spare1_ptr;
    lv2_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = sv39_kernel_pte(l1_frame_addr,
                                                           true, true,
                                                           false, true,
                                                           false);
    sys_tlb_flush_all();
    for (uint32_t c = 0; c < nr_l0_maps; c++) {
        l1_index = sv39_vpn1(v_addr_ptr);
        if (!sv39_is_valid(spare_ptr[l1_index])) {
            l0_frame_addr = pf_bitmap_alloc_frame();
            spare_ptr[l1_index] = sv39_kernel_pte_pointer(l0_frame_addr, true);
        } else {
            l0_frame_addr = sv39_pte_ppn(spare_ptr[l1_index]) * FRAME_SIZE;
        }
        sys_kassert(l0_frame_addr != 0);
        mem_placement_map_segment_sv39_lv0(l0_frame_addr, &v_addr_ptr,
                                           &p_addr_ptr, &nr_ptes, seg_type);
    }
    lv2_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = 0;
}

void mem_set_kernel_virtual_start_address(rvu_word address) {
#ifdef RV64
    kernel_virtual_start_index = sv39_vpn2(address);
#else
    kernel_virtual_start_index = sv32_vpn1(address);
#endif
}

uint32_t mem_size_in_pages(uint32_t bytes) {
    uint32_t num_pages = bytes / PAGE_SIZE;
    uint32_t num_pages_remain = bytes % PAGE_SIZE;
    num_pages = num_pages_remain > 0 ? num_pages + 1 : num_pages;
    return num_pages;
}

void mem_setup_hh_page_table_sv32(KernelLinkerConfig* config) {
    // assume no second level pages exist
    // assume that we have a recursive PTE in the last of the page table
    // MAP TEXT SEGMENT
    rvu_word text_v_addr = config->kernel_text_begin_virtual;
    rvu_word kernel_text_size = config->kernel_text_end - config->kernel_text_begin;
    mem_placement_map_segment(config->kernel_text_begin, text_v_addr, kernel_text_size, TEXT_SEGMENT);
    // MAP RO SEGMENT
    // TODO: verify that size is a multiple of frame size
    rvu_word ro_v_addr = config->kernel_ro_data_begin_virtual;
    rvu_word kernel_ro_size = config->kernel_ro_data_end - config->kernel_ro_data_begin;
    mem_placement_map_segment(config->kernel_ro_data_begin, ro_v_addr, kernel_ro_size, READ_ONLY_SEGMENT);
    // MAP DATA SEGMENT
    // TODO: verify that size is a multiple of frame size
    rvu_word data_v_addr = config->kernel_data_begin_virtual;
    rvu_word kernel_data_size = config->kernel_ro_data_end - config->kernel_ro_data_begin;
    mem_placement_map_segment(config->kernel_data_begin, data_v_addr, kernel_data_size, DATA_SEGMENT);
    // MAP BSS SEGMENT
    // TODO: verify that size is a multiple of frame size
    rvu_word bss_v_addr = config->kernel_bss_begin_virtual;
    // FIXME: why is the mapping off by one?
    rvu_word kernel_bss_size = config->kernel_bss_end - config->kernel_bss_begin + FRAME_SIZE;
    mem_placement_map_segment(config->kernel_bss_begin, bss_v_addr, kernel_bss_size, DATA_SEGMENT);
    // TODO: map heap?
}

void mem_setup_hh_page_table_sv39(KernelLinkerConfig* config) {
    uint32_t l1_frame_addr = pf_bitmap_alloc_frame();
    // MAP TEXT SEGMENT
    rvu_word text_v_addr = config->kernel_text_begin_virtual;
    rvu_word kernel_text_size = config->kernel_text_end - config->kernel_text_begin;
    mem_placement_map_hh_segment_sv39_lv1(l1_frame_addr,
                                          config->kernel_text_begin,
                                          text_v_addr, kernel_text_size, TEXT_SEGMENT);
    // RO SEGMENT
    rvu_word ro_v_addr = config->kernel_ro_data_begin_virtual;
    rvu_word kernel_ro_size = config->kernel_ro_data_end - config->kernel_ro_data_begin;
    mem_placement_map_hh_segment_sv39_lv1(l1_frame_addr,
                                       config->kernel_ro_data_begin,
                                       ro_v_addr, kernel_ro_size, READ_ONLY_SEGMENT);

    // MAP DATA SEGMENT
    // TODO: verify that size is a multiple of frame size
    rvu_word data_v_addr = config->kernel_data_begin_virtual;
    rvu_word kernel_data_size = config->kernel_ro_data_end - config->kernel_ro_data_begin;
    mem_placement_map_hh_segment_sv39_lv1(l1_frame_addr,
                                       config->kernel_data_begin,
                                       data_v_addr, kernel_data_size, DATA_SEGMENT);
    // MAP BSS SEGMENT
    // TODO: verify that size is a multiple of frame size
    rvu_word bss_v_addr = config->kernel_bss_begin_virtual;
    // FIXME: why is the mapping off by one?
    rvu_word kernel_bss_size = config->kernel_bss_end - config->kernel_bss_begin + FRAME_SIZE;
    mem_placement_map_hh_segment_sv39_lv1(l1_frame_addr,
                                       config->kernel_bss_begin,
                                       bss_v_addr, kernel_bss_size, BSS_SEGMENT);
    // TODO: map heap?
    // HEAP SEGMENT
    uint32_t l2_index = sv39_vpn2(config->kernel_virtual_base);
    uint64_t* lv2_ptr = page_table_sv39_lv2_ptr;
    lv2_ptr[l2_index] = sv39_kernel_pte_pointer(l1_frame_addr, true);
    sys_tlb_flush_all();
}

void mem_setup_page_table(KernelLinkerConfig* config) {
#ifdef RV64
    mem_setup_hh_page_table_sv39(config);
#else
    mem_setup_hh_page_table_sv32(config);
#endif
}

void mem_clone_kernel_address_space(rvu_word page) {
#ifdef RV64
    uint64_t spare_pte = sv39_kernel_pte(page,
                                         true, true,
                                         false, true, false);
    uint64_t* lv2_ptr = page_table_sv39_lv2_ptr;
    lv2_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = spare_pte;
    sys_tlb_flush_all();
    uint64_t* spare_table_ptr = page_table_sv39_lv2_spare1_ptr;
    kprintf(K_DEBUG,
            "mem [clone]: cloning kernel address space to page %p...\n", page);
    for (uint32_t i = 0; i < 512; i++) {
        spare_table_ptr[i] = lv2_ptr[i];
    }
    // recursive maps
    spare_table_ptr[511] = sv39_kernel_pte_pointer(page, true);
    spare_table_ptr[510] = sv39_kernel_pte(page, true, true,
                                           false, true, false);
    lv2_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = 0;
#else
    uint32_t spare_pte = sv32_kernel_pte(page, true, true,
                                         false, true, false);
    uint32_t* lv1_ptr = page_table_lv1_ptr;
    lv1_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = spare_pte;
    sys_tlb_flush_all();
    uint32_t* spare_table_ptr = page_table_lv1_spare_ptr;
    if (kernel_virtual_start_index == 0) {
        kputs(K_DEBUG,
              "mem [clone]: kernel_virtual_start_index == 0\n");
        sys_kassert(false);
    }
    kprintf(K_DEBUG,
            "mem [clone]: cloning kernel address space to page %p...\n", page);
    for (uint32_t i = kernel_virtual_start_index; i < 1024; i++) {
        spare_table_ptr[i] = lv1_ptr[i];
    }
    // set up recursive maps
    spare_table_ptr[1023] = sv32_kernel_pte_pointer(page, true);
    spare_table_ptr[1022] = sv32_kernel_pte(page, true, true,
                                            false, true, false);
    lv1_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = 0;
#endif
}

void mem_clone_kernel_address_space_sv39(uint64_t page) {
    uint64_t spare_pte = sv39_kernel_pte(page,
                                         true, true,
                                         false, true, false);
    uint64_t* lv1_ptr = page_table_sv39_lv2_ptr;
    lv1_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = spare_pte;
    sys_tlb_flush_all();
    uint64_t* spare_table_ptr = page_table_sv39_lv2_spare1_ptr;
    kprintf(K_DEBUG,
            "mem [clone]: cloning kernel address space to page %p...\n", page);
    for (uint32_t i = kernel_virtual_start_index; i < 512; i++) {
        spare_table_ptr[i] = lv1_ptr[i];
    }
    // recursive maps
    spare_table_ptr[511] = sv39_kernel_pte_pointer(page, true);
    spare_table_ptr[510] = sv39_kernel_pte(page, true, true,
                                           false, true, false);
    lv1_ptr[ROOT_PAGE_TABLE_SPARE_INDEX] = 0;
}


void map_device_tree_area(rvu_word device_tree_addr) {
    // for now we will just map the device tree area 1:1
#ifdef RV64
    //
#else
    uint32_t* page_table_lv1 = page_table_lv1_ptr;
    uint32_t tree_pde_index = sv32_vpn1(device_tree_addr);
    uint32_t tree_aligned_addr = (device_tree_addr >> 22U) << 22U;
    uint32_t tree_pte = sv32_kernel_pte(tree_aligned_addr,
                                        true, false,
                                        false, true, false);
    page_table_lv1[tree_pde_index] = tree_pte;
    sys_table_flush_all();
#endif
}

void create_early_identity_map(rvu_word firmware_addr, rvu_word map_size) {
#ifndef RV64
    uint32_t pte = 0;
    uint32_t mb4 = 0x1 << 22U;
    uint32_t num_mappings = map_size >> 22U;
    uint32_t pde_index = sv32_vpn1(firmware_addr);
    uint32_t aligned_addr = (firmware_addr >> 22U) << 22U;
    uint32_t* page_table_lv1 = page_table_lv1_ptr;
    for (uint32_t i = 0, p = pde_index; i < num_mappings; i++,p++) {
        pte = sv32_kernel_pte(aligned_addr,
                              true, true,
                              true, true, false);
        page_table_lv1[p] = pte;
        aligned_addr += mb4;
    }
    // tlb flush?
    sys_tlb_flush_all();
#endif
}