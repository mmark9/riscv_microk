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
#include "memory.h"

#include <stdint.h>
#include <stdbool.h>

const char* BANNER = " _____ ___  ___ ___ ___  __   __  _  _____ ___ _  _ ___ _    \n"
                     " |_   _| _ \\/ __|_ _/ __|_\\ \\ / / | |/ / __| _ \\ \\| | __| |   \n"
                     "   | | |   /\\__ \\| | (_|___\\ V /  | ' <| _||   / .` | _|| |__ \n"
                     "   |_| |_|_\\|___/___\\___|   \\_/   |_|\\_\\___|_|_\\_|\\_|___|____|\n"
                     "                                                              \n";


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
    kprintf("boot: setting up higher half of address space...\n");
    mem_setup_page_table(&linker_config);
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

