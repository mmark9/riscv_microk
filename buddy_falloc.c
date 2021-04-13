#include "system.h"
#include "devtree.h"
#include "bit_utils.h"
#include "page_frame.h"

#include <stdint.h>
#include <stdbool.h>

#define MAX_ORDER 5

// FIXME: need locks
static struct BuddyState {
    bool base_memory_set;
    bool initialized;
    uint32_t base_addr;
    uint32_t nr_pages_allocated;
    uint32_t nr_pages_total;
    uint32_t max_order;
} buddy_state;

void zero_mem(void* address, uint32_t size) {
    char* ptr = (char*)address;
    for (uint32_t i = 0; i < size; i++) {
        *ptr = 0;
        ptr += 1;
    }
}

typedef struct buddy_item {
    // TODO: make this a uint32_t
    uint32_t order;
    uint32_t address;
    struct buddy_item* left;
    struct buddy_item* right;
    bool free;
} BuddyItem;

typedef struct {
    bool valid;
    uint32_t address;
    uint32_t order;
} BuddyAllocResult;

typedef struct {
    BuddyItem* head;
    BuddyItem* free_tail;
    BuddyItem* free_head;
    uint32_t num_free;
    uint32_t num_items;
    uint32_t order;
} BuddyHeader;

uint32_t order_to_size(uint8_t order) {
    return (0x1 << order) * FRAME_SIZE;
}

int32_t buddy_index(uint32_t address, uint32_t order) {
    if (order > MAX_ORDER)
        return -1;
    uint32_t order_size = order_to_size(order);
    uint32_t effective_addr = address - buddy_state.base_addr;
    int32_t index = effective_addr / order_size;
    return index;
}

uint32_t buddy_address(int32_t index, uint32_t order) {
    if (order > MAX_ORDER)
        return 0;
    if (index < 0)
        return 0;
    uint32_t order_size = order_to_size(order);
    uint32_t address = order_size * index;
    return address;
}

#define NUM_BUDDY_FRAMES 32768

#define NUM_ORDER_0_REGIONS NUM_BUDDY_FRAMES
#define NUM_ORDER_1_REGIONS NUM_BUDDY_FRAMES/2
#define NUM_ORDER_2_REGIONS NUM_BUDDY_FRAMES/4
#define NUM_ORDER_3_REGIONS NUM_BUDDY_FRAMES/8
#define NUM_ORDER_4_REGIONS NUM_BUDDY_FRAMES/16
#define NUM_ORDER_5_REGIONS NUM_BUDDY_FRAMES/32

BuddyItem order0[NUM_ORDER_0_REGIONS];
BuddyItem order1[NUM_ORDER_1_REGIONS];
BuddyItem order2[NUM_ORDER_2_REGIONS];
BuddyItem order3[NUM_ORDER_3_REGIONS];
BuddyItem order4[NUM_ORDER_4_REGIONS];
BuddyItem order5[NUM_ORDER_5_REGIONS];

BuddyHeader buddy_list[6];

int32_t num_regions_of_order(int32_t order) {
    if (order < 0 || order > MAX_ORDER)
        return -1;
    int32_t num_regions = NUM_BUDDY_FRAMES / (0x1 << order);
    return num_regions;
}

bool address_is_valid_for_order(uint32_t address, int32_t order) {
    return true;
}

void buddy_list_del(uint32_t address, int32_t order) {
    if (!address_is_valid_for_order(address, order))
        return;
    if (order < 0 || order > MAX_ORDER)
        return;
    int32_t index = buddy_index(address, order);
    if (index < 0 || index >= buddy_list[order].num_items)
        return;
    BuddyItem* tmp_buddy = &buddy_list[order].head[index];
    if (!tmp_buddy->free)
        return;
    tmp_buddy->free = false;
    BuddyItem* head = buddy_list[order].free_head;
    BuddyItem* tail = buddy_list[order].free_tail;
    if (head == tail) {
        buddy_list[order].free_head = 0;
    } else if (tmp_buddy == head) {
        buddy_list[order].free_head = tmp_buddy->right;
        buddy_list[order].free_head->left = tmp_buddy->left;
        tail->right = buddy_list[order].free_head;
    } else if (tmp_buddy == tail) {
        buddy_list[order].free_tail = tmp_buddy->left;
        buddy_list[order].free_tail->right = tmp_buddy->right;
        head->left = buddy_list[order].free_tail;
    } else {
        tmp_buddy->left->right = tmp_buddy->right;
        tmp_buddy->right->left = tmp_buddy->left;
    }
    tmp_buddy->left = 0;
    tmp_buddy->right = 0;
    buddy_list[order].num_free -= 1;
}

void buddy_list_add(uint32_t address, int32_t order) {
    if (!address_is_valid_for_order(address, order))
        return;
    if (order < 0 || order > MAX_ORDER)
        return;
    int32_t index = buddy_index(address, order);
    if (index < 0 || index >= buddy_list[order].num_items)
        return;
    BuddyItem* tmp_buddy = &buddy_list[order].head[index];
    // TODO: prevent double frees
    //if (tmp_buddy->free)
    //return;
    tmp_buddy->free = true;
    tmp_buddy->address = address;
    tmp_buddy->order = order;
    BuddyItem* head = buddy_list[order].free_head;
    BuddyItem* tail = buddy_list[order].free_tail;
    if (buddy_list[order].num_free > 0) {
        tmp_buddy->right = head;
        tmp_buddy->left = tail;
        head->left = tmp_buddy;
        tail->right = tmp_buddy;
        buddy_list[order].free_tail = tmp_buddy;
    } else {
        buddy_list[order].free_head = tmp_buddy;
        buddy_list[order].free_tail = tmp_buddy;
        tmp_buddy->left = tmp_buddy;
        tmp_buddy->right = tmp_buddy;
    }
    buddy_list[order].num_free += 1;
}

int32_t index_of_buddy(uint32_t address, int32_t order) {
    if (order < 0  || order > MAX_ORDER)
        return -1;
    int32_t index = buddy_index(address, order);
    int32_t buddy_index = index % 2 == 0 ? index + 1 : index - 1;
    return buddy_index;
}

uint32_t merged_buddy_address(const BuddyItem* a, const BuddyItem* b) {
    if (a == 0 || b == 0)
        return 0;
    uint32_t address = (uint32_t)a->address < (uint32_t)b->address ? a->address : b->address;
    return address;
}

void buddy_free(uint32_t address, int32_t order) {
    if (order < 0 || order > MAX_ORDER)
        return;
    BuddyItem* buddy1 = 0;
    BuddyItem* buddy2 = 0;
    int32_t buddy1_index = 0;
    int32_t buddy2_index = 0;
    uint32_t address_ptr = address;
    uint32_t merge_address = 0;
    int32_t order_ptr = order;
    uint32_t nr_pages = 1U << order;
    if (pf_bitmap_region_is_free(address, 1U << order)) {
        kprintf("region [base: 0x%08x | nr_pages: %u] is already free!\n",
               address, nr_pages);
        return;
    }
    buddy_list_add(address_ptr, order_ptr);
    while (order_ptr < MAX_ORDER) {
        buddy1_index = buddy_index(address_ptr, order_ptr);
        buddy2_index = index_of_buddy(address_ptr, order_ptr);
        buddy1 = &buddy_list[order_ptr].head[buddy1_index];
        buddy2 = &buddy_list[order_ptr].head[buddy2_index];
        merge_address = merged_buddy_address(buddy1, buddy2);
        if (!buddy1->free || !buddy2->free) {
            kprintf("buddy_alloc: cannot merge buddy [0x%08x | free? %s] with buddy [0x%08x | free? %s] |"
                   " merge address = 0x%08x | order = %u\n", buddy1->address,
                   buddy1->free ? "yes" : "no", buddy2->address,
                   buddy2->free ? "yes" : "no", merge_address, order_ptr);
            break;
        }
        kprintf("buddy_alloc: merging buddy [0x%08x | free? %s] with buddy [0x%08x | free? %s] | "
               "merge address = 0x%08x | order = %u\n", buddy1->address,
               buddy1->free ? "yes" : "no", buddy2->address, buddy2->free ? "yes" : "no",
               merge_address, order_ptr);
        buddy_list_del(buddy1->address, order_ptr);
        buddy_list_del(buddy2->address, order_ptr);
        order_ptr += 1;
        buddy_list_add(merge_address, order_ptr);
        address_ptr = merge_address;
    }
    buddy_state.nr_pages_allocated -= (1U << order);
    pf_bitmap_mark_region_free(address, 1U << order);
}

bool buddy_split(int32_t order) {
    if (buddy_list[order].num_free > 0)
        return true;
    if (order > MAX_ORDER)
        return false;
    int32_t order_ptr_high = order;
    while (order_ptr_high <= MAX_ORDER) {
        if (buddy_list[order_ptr_high].num_free == 0)
            order_ptr_high += 1;
        else
            break;
    }
    if (order_ptr_high > MAX_ORDER) {
        kprintf("buddy_alloc: cannot find any regions of order %d | size %u\n", order, 0x1 << order);
        return false;
    }
    kprintf("buddy_alloc: found free region of order %d | size %u\n", order_ptr_high, 0x1 << order_ptr_high);
    BuddyItem* large_region = 0;
    BuddyItem* left_split = 0;
    BuddyItem* right_split = 0;
    int32_t left_index = 0;
    int32_t right_index = 0;
    uint32_t left_address = 0;
    uint32_t right_address;
    uint32_t order_size = 0;
    while (order_ptr_high > order) {
        order_size = order_to_size(order_ptr_high);
        large_region = buddy_list[order_ptr_high].free_head;
        left_address = large_region->address;
        right_address = left_address + order_size / 2;
        buddy_list_del(large_region->address, order_ptr_high);
        order_ptr_high -= 1;

        left_index = buddy_index(left_address, order_ptr_high);
        right_index = buddy_index(right_address, order_ptr_high);
        left_split = &buddy_list[order_ptr_high].head[left_index];
        right_split = &buddy_list[order_ptr_high].head[right_index];

        buddy_list_add(left_address, order_ptr_high);
        buddy_list_add(right_address, order_ptr_high);
    }
    return true;
}

BuddyAllocResult buddy_allocate(int32_t order) {
    // NOTE: we could encode error codes in res
    // NOTE: might want to relax this kassert for testing
    kassert(buddy_state.initialized);
    BuddyAllocResult res = {
            .valid = false,
            .order = 0,
            .address = 0
    };
    if (order < 0 || order > MAX_ORDER) {
        return res;
    }
    if (buddy_list[order].num_free == 0 && !buddy_split(order))
        return res;
    BuddyItem* next_buddy = buddy_list[order].free_head;
    buddy_list_del(next_buddy->address, order);
    buddy_state.nr_pages_allocated += ( 1U << next_buddy->order);
    res.address = next_buddy->address;
    res.order = next_buddy->order;
    res.valid = true;
    pf_bitmap_mark_region_allocated(next_buddy->address, 1U << order);
    return res;
}

BuddyItem* buddy_allocate_raw(int32_t order) {
    // NOTE: we could encode error codes
    if (order < 0 || order > MAX_ORDER) {
        return 0;
    }
    if (!buddy_split(order))
        return 0;
    BuddyItem* next_buddy = buddy_list[order].free_head;
    buddy_list_del(next_buddy->address, order);
    return next_buddy;
}

void buddy_reset() {
    buddy_list[0].num_free = 0;
    buddy_list[0].num_items = NUM_ORDER_0_REGIONS;
    buddy_list[0].head = order0;
    buddy_list[0].free_head = 0;

    buddy_list[1].num_free = 0;
    buddy_list[1].num_items = NUM_ORDER_1_REGIONS;
    buddy_list[1].head = order1;
    buddy_list[1].free_head = 0;

    buddy_list[2].num_free = 0;
    buddy_list[2].num_items = NUM_ORDER_2_REGIONS;
    buddy_list[2].head = order2;
    buddy_list[2].free_head = 0;

    buddy_list[3].num_free = 0;
    buddy_list[3].num_items = NUM_ORDER_3_REGIONS;
    buddy_list[3].head = order3;
    buddy_list[3].free_head = 0;

    buddy_list[4].num_free = 0;
    buddy_list[4].num_items = NUM_ORDER_4_REGIONS;
    buddy_list[4].head = order4;
    buddy_list[4].free_head = 0;

    buddy_list[5].num_free = 0;
    buddy_list[5].num_items = NUM_ORDER_5_REGIONS;
    buddy_list[5].head = order5;
    buddy_list[5].free_head = 0;
}

void init_buddy_list() {
    buddy_reset();
    int32_t local_max_order = 2;
    int32_t num_regions = 0;
    BuddyItem* buddies = 0;
    uint32_t address_ptr = 0;
    uint32_t order_size = 0;
    uint32_t pfn = 0;
    for (uint32_t order = 0; order <= local_max_order; order++) {
        num_regions = num_regions_of_order(order);
        buddies = buddy_list[order].head;
        order_size = order_to_size(order);
        address_ptr = 0;
        for (uint32_t i = 0; i < num_regions; i++) {
            buddies[i].order = order;
            buddies[i].address = buddy_address(i, order);
            pfn = bits(address_ptr, 12, 20);
            if (order == local_max_order && pf_bitmap_bit_is_on(pfn)) {
                buddy_list_add(address_ptr, order);
            } else {
                buddies[i].left = 0;
                buddies[i].right = 0;
                buddies[i].free = false;
            }
            buddies[i].address = address_ptr;
            address_ptr += order_size;
        }
        if (order != local_max_order)
            buddy_list[order].free_head = 0;
        buddy_list[order].num_items = num_regions;
    }
}

int buddy_memory_range(uint32_t* base_out,
                       uint32_t* size_out,
                       DeviceTreeContext* ctx) {
    DeviceTreeProp prop;
    int res = devtree_property("reg", &prop, ctx);
    kassert(res == 0);
    res = devtree_word_at_index(0, &prop, base_out, ctx);
    kassert(res == 0);
    res = devtree_word_at_index(1, &prop, size_out, ctx);
    kassert(res == 0);
    return 0;
}

void buddy_add_region(uint32_t address, uint32_t order, uint32_t nr_regions) {
    uint32_t addr_ptr = address;
    uint32_t region_size = (1U << order) * FRAME_SIZE;
    for (uint32_t i = 0; i < nr_regions; i++) {
        buddy_list_add(addr_ptr, order);
        addr_ptr += region_size;
    }
}

void buddy_process_memory_range(uint32_t base_addr, uint32_t region_size) {
    kassert(region_size % FRAME_SIZE == 0);
    uint32_t nr_pages = region_size / FRAME_SIZE;
    // zero page size is invalid
    kassert(nr_pages != 0);
    int order = MAX_ORDER;
    uint32_t nr_pages_left = nr_pages;
    uint32_t nr_regions = 0;
    uint32_t order_nr_pages = 0;
    uint32_t address_ptr = base_addr;
    do  {
        if (nr_pages_left == 0)
            break;
        order_nr_pages = 1U << order;
        if (nr_pages_left < order_nr_pages) {
            // not enough pages to fit in this free list
            order -= 1;
            continue;
        }
        nr_regions = nr_pages_left / order_nr_pages;
        nr_pages_left -= (order_nr_pages * nr_regions);
        // TODO: make this an integer not a pointer
        buddy_add_region(address_ptr, order, nr_regions);
        address_ptr += (nr_regions * order_nr_pages * FRAME_SIZE);
        order -= 1;
    } while (order >= 0);
}

void buddy_process_memory_node(DeviceTreeContext* ctx) {
    uint32_t base_addr = 0;
    uint32_t region_size = 0;
    int res = buddy_memory_range(&base_addr, &region_size, ctx);
    kassert(res == 0);
    // we assume that memory can always a multiple of the frame size
    buddy_process_memory_range(base_addr, region_size);
}

void buddy_load_devtree_memory_stats(DeviceTreeContext* ctx) {
    uint32_t region_addr = 0;
    uint32_t region_size = 0;
    uint32_t region_nr_pages = 0;
    buddy_state.base_addr = 0;
    buddy_state.max_order = MAX_ORDER;
    buddy_state.base_memory_set = false;
    buddy_state.nr_pages_allocated = 0;
    buddy_state.nr_pages_total = 0;
    uint32_t min_base_addr = UINT32_MAX;
    uint32_t node_count = devtree_child_node_count(ctx);
    for (uint32_t i = 0; i < node_count; i++) {
        if (streq_node(devtree_child_name(i, ctx), "memory")) {
            devtree_move_to_child(i, ctx);
            buddy_memory_range(&region_addr, &region_size, ctx);
            region_nr_pages = region_size / FRAME_SIZE;
            // memory nodes should declare ranges multiple of a page
            kassert((region_size % FRAME_SIZE) == 0);
            buddy_state.nr_pages_total += region_nr_pages;
            min_base_addr = region_addr < min_base_addr ? region_addr : min_base_addr;
            devtree_move_to_root(ctx);
        }
    }
    kassert(min_base_addr != UINT32_MAX);
    buddy_state.base_addr = min_base_addr;
    buddy_state.base_memory_set = true;
}

void buddy_init_from_dev_tree(DeviceTreeContext* ctx) {
    buddy_reset();
    kassert(!buddy_state.initialized);
    uint32_t node_count = devtree_child_node_count(ctx);
    for (uint32_t i = 0; i < node_count; i++) {
        if (streq_node(devtree_child_name(i, ctx), "memory")) {
            devtree_move_to_child(i, ctx);
            buddy_process_memory_node(ctx);
            devtree_move_to_root(ctx);
        }
    }
    buddy_state.initialized = true;
}

void buddy_init_from_range(uint32_t base_addr, uint32_t size) {
    buddy_reset();
    buddy_state.base_addr = base_addr;
    buddy_state.nr_pages_total = (size / FRAME_SIZE);
    buddy_process_memory_range(base_addr, size);
    buddy_state.initialized = true;
}
