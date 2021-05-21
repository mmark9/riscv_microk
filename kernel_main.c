#include "sched.h"
#include "kprint.h"
#include "system.h"
#include "interrupt.h"
#include "sbi_relay.h"
#include "constants.h"
#include "time.h"
#include "memory.h"
#include "simple_falloc.h"
#include "page_frame.h"

#include <stdint.h>
#include <stdbool.h>

const char* BANNER = " _____ ___  ___ ___ ___  __   __  _  _____ ___ _  _ ___ _    \n"
                     " |_   _| _ \\/ __|_ _/ __|_\\ \\ / / | |/ / __| _ \\ \\| | __| |   \n"
                     "   | | |   /\\__ \\| | (_|___\\ V /  | ' <| _||   / .` | _|| |__ \n"
                     "   |_| |_|_\\|___/___\\___|   \\_/   |_|\\_\\___|_|_\\_|\\_|___|____|\n"
                     "                                                              \n";

extern struct thread_tcb* current_thread;

void print_banner() {
    kputs("\n\n");
    kputs(BANNER);
}

void thread_func1() {
    for (uint32_t i = 0; i < 40; i++) {
        kprintf("thread %d: executing iteration %d...\n",
                current_thread->thread_id, i);
        // hacky yield
        if (i % 20 == 0) {
            sched_enqueue(current_thread);
            sys_ebreak();
        }
    }
}

void thread_func2() {
    for (uint32_t i = 0; i < 50; i++) {
        kprintf("thread %d: executing iteration %d...\n",
                current_thread->thread_id, i);
        // hacky yield
        if (i % 10 == 0) {
            sched_enqueue(current_thread);
            sys_ebreak();
        }
    }
}

void thread_func3() {
    uint32_t accumulator = 0;
    for (uint32_t i = 0;; i++) {
        if (i % 10000 == 0) {
            kprintf("thread %d: executing "
                    "preemptive thread (iter: %d)...\n",
                    current_thread->thread_id, i);
            accumulator += i;
        }
    }
}

struct thread_tcb thread1;
struct thread_tcb thread2;

void kernel_main(
        uint32_t hart_id,
		void* config,
		bool use_dev_tree,
		KernelLinkerConfig linker_config) {
    print_banner();
    struct sbiret impl_id = sbi_relay_get_impl_id();
    struct sbiret march_id = sbi_relay_get_marchid();
    struct sbiret vendor_id = sbi_relay_get_mvendorid();
    kprintf("system: running on core %d | march_id = %d "
            "| vendor_id = %d | impl_id = %d\n", hart_id,
            march_id.value, vendor_id.value, impl_id.value);
    kprintf("boot: kernel image size %d\n", linker_config.kernel_size_in_bytes);
    // for now map 16 MiB
    uint32_t identity_map_size = (0x1 << 22U) * 8;
    // map 8 MiB for kernel area initially
    kputs("system: setting up supervisor level interrupts..\n");
    setup_trap_handlers();
    sys_enable_supervisor_interrupts();
    sys_enable_supervisor_timer_interrupts();
    sys_enable_supervisor_software_interrupts();
    uint32_t higher_half_map_size = identity_map_size / 2;
    kputs("system: setting up early kernel address space.\n");
    create_early_identity_map(linker_config.firmware_load_address,
                              identity_map_size);
    map_device_tree_area((uint32_t)config);
    kputs("system: loading memory config from device tree..\n");
    uint64_t mem_range = memory_range_from_device_tree(config);
    uint32_t mem_base = mem_range >> 32;
    uint32_t mem_size = UINT32_MAX & mem_range;
    kprintf("system: memory_start = %p | memory_size = %u\n",
            mem_base, mem_size);
    kputs("system: setting up frame bitmap...\n");
    init_frame_bitmap_from_linker_config(&linker_config);
    kprintf("boot: setting up higher half of address space...\n");
    mem_setup_page_table(&linker_config);
    kputs("system: setting up page frame allocator...\n");
    simple_falloc_init_from_frame_bitmap(mem_base, mem_size);
    mem_set_kernel_virtual_start_address(linker_config.kernel_virtual_base);
    // TODO: make heap setup flexible
    uint32_t kheap_size = (0x1U << 20U); // 1MiB
    uint32_t kheap_start = linker_config.kernel_virtual_base +
            higher_half_map_size - kheap_size;
    // aligned address
    kheap_start = (kheap_start >> 12) << 12;
    kprintf("system: setting heap @ %p | size = %u bytes\n",
            kheap_start, kheap_size);
    setup_kernel_heap(kheap_start, kheap_size);
    kputs("system: initializing scheduler\n");
    sched_init();
    kputs("system: starting first thread\n");
    sched_init_thread(&thread1, thread_func3);
    sched_init_thread(&thread2, thread_func3);
    sched_enqueue(&thread1);
    sched_enqueue(&thread2);
    time_capture_boot_time();
    time_schedule_next_timer(TIMER_TICK_INTERVAL);
    // at this point we either jump to another thread
    // or just wait for the timer interrupt to fire
    while (true) {
        continue;
    }
}

