#include "csr.h"
#include "sched.h"
#include "kmalloc.h"
#include "page_table.h"
#include "kheap.h"
#include "bit_utils.h"
#include "buddy_falloc.h"
#include "kprint.h"
#include "interrupt.h"
#include "sbi_relay.h"
#include "buddy_falloc.h"
#include "page_frame.h"

#include <stdint.h>
#include <stdbool.h>

const char* BANNER = " _____ ___  ___ ___ ___  __   __  _  _____ ___ _  _ ___ _    \n"
                     " |_   _| _ \\/ __|_ _/ __|_\\ \\ / / | |/ / __| _ \\ \\| | __| |   \n"
                     "   | | |   /\\__ \\| | (_|___\\ V /  | ' <| _||   / .` | _|| |__ \n"
                     "   |_| |_|_\\|___/___\\___|   \\_/   |_|\\_\\___|_|_\\_|\\_|___|____|\n"
                     "                                                              \n";

extern void halt_system(void);

extern uint32_t page_directory[1024];

typedef struct {
    uint32_t firmware_load_address;
    uint32_t kernel_load_address;
    uint32_t kernel_text_begin;
    uint32_t kernel_text_end;
    uint32_t kernel_ro_data_begin;
    uint32_t kernel_ro_data_end;
    uint32_t kernel_data_begin;
    uint32_t kernel_data_end;
    uint32_t kernel_bss_begin;
    uint32_t kernel_bss_end;
    uint32_t kernel_virtual_base;
    uint32_t kernel_virtual_end;
    uint32_t kernel_size_in_bytes;
} KernelLinkerConfig;

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
    uint32_t old_pte = page_directory[pde_index];
    for (uint32_t i = 0, p = pde_index; i < num_4mb_mappings; i++,p++) {
        new_pte = sv32_kernel_pte(paddr_ptr, true,
                                  true, true, true);
        page_directory[p] = new_pte;
        vaddr_ptr += mb4;
        paddr_ptr += mb4;
    }
    // tlb flush?
}

void map_device_tree_area(uint32_t device_tree_addr) {
    // for now we will just map the device tree area 1:1
    uint32_t tree_pde_index = sv32_vpn1(device_tree_addr);
    uint32_t tree_aligned_addr = (device_tree_addr >> 22U) << 22U;
    uint32_t tree_pte = sv32_kernel_pte(tree_aligned_addr,
                                        true, false,
                                        false, true);
    page_directory[tree_pde_index] = tree_pte;
}

void create_early_identity_map(uint32_t firmware_addr, uint32_t map_size) {
    uint32_t pte = 0;
    uint32_t mb4 = 0x1 << 22U;
    uint32_t num_mappings = map_size >> 22U;
    uint32_t pde_index = sv32_vpn1(firmware_addr);
    uint32_t aligned_addr = (firmware_addr >> 22U) << 22U;
    for (uint32_t i = 0, p = pde_index; i < num_mappings; i++,p++) {
        pte = sv32_kernel_pte(aligned_addr,
                              true, true,
                              true, true);
        page_directory[p] = pte;
        aligned_addr += mb4;
    }
    // tlb flush?
}

void setup_kernel_heap(uint32_t heap_base, uint32_t heap_size) {
    kheap_init(heap_base, heap_size);
    init_malloc((void*)kheap_start(), kheap_size());
}

void print_banner() {
    kputs("\n\n");
    kputs(BANNER);
}

void kernel_main(
        uint32_t hart_id,
		void* config,
		bool use_dev_tree,
		KernelLinkerConfig linker_config) {
    print_banner();
    struct sbiret impl_id = sbi_relay_get_impl_id();
    struct sbiret march_id = sbi_relay_get_marchid();
    struct sbiret vendor_id = sbi_relay_get_mvendorid();
    kprintf("boot: running on core %d | march_id = %d "
            "| vendor_id = %d | impl_id = %d\n", hart_id,
            march_id.value, vendor_id.value, impl_id.value);
    // for now map 16 MiB
    uint32_t identity_map_size = (0x1 << 22U) * 8;
    // map 8 MiB for kernel area initially
    uint32_t higher_half_map_size = identity_map_size / 2;
    kputs("boot: setting up early kernel address space.\n");
    create_early_identity_map(linker_config.firmware_load_address,
                              identity_map_size);
    map_device_tree_area((uint32_t)config);
    map_kernel_higher_half(linker_config.kernel_load_address,
                           linker_config.kernel_virtual_base,
                           higher_half_map_size);
    kputs("boot: loading memory config from device tree..\n");
    uint64_t mem_range = memory_range_from_device_tree(config);
    uint32_t mem_base = mem_range >> 32;
    uint32_t mem_size = UINT32_MAX & mem_range;
    kprintf("boot: memory_start = %p | memory_size = %u\n",
            mem_base, mem_size);
    kputs("boot: initializing memory subsystem...\n");
    setup_memory_subsystem(linker_config.kernel_load_address,
                           mem_base, mem_size,
                           higher_half_map_size);
    // TODO: make heap setup flexible
    uint32_t kheap_size = (0x1U << 20U); // 1MiB
    uint32_t kheap_start = linker_config.kernel_virtual_base +
            higher_half_map_size - kheap_size;
    kprintf("boot: setting heap @ %p | size = %u bytes\n",
            kheap_start, kheap_size);
    setup_kernel_heap(kheap_start, kheap_size);
    kputs("boot: setting up supervisor level interrupts..\n");
    setup_trap_handlers();
    enable_interrupts();
    // at this point we either jump to another thread
    // or just wait for the timer interrupt to fire
    while (true) {
        continue;
    }
}

