#include "kapps.h"
#include "sched.h"
#include "kprint.h"
#include "system.h"
#include "interrupt.h"
#include "sbi_relay.h"
#include "constants.h"
#include "utils.h"
#include "time.h"
#include "kmalloc.h"
#include "memory.h"
#include "syscalls.h"
#include "simple_falloc.h"
#include "page_frame.h"
#include "terminal.h"

#include <stdint.h>
#include <stdbool.h>

const char* BANNER = " _____    _                           _____ _____ \n"
                     "|_   _|  (_)                         |  _  /  ___|\n"
                     "  | |_ __ _ _ __ ___ _ __ ___   ___  | | | \\ `--. \n"
                     "  | | '__| | '__/ _ \\ '_ ` _ \\ / _ \\ | | | |`--. \\\n"
                     "  | | |  | | | |  __/ | | | | |  __/ \\ \\_/ /\\__/ /\n"
                     "  \\_/_|  |_|_|  \\___|_| |_| |_|\\___|  \\___/\\____/ \n"
                     "                                                  \n";

void print_banner() {
    kputs(K_INFO, "\n\n");
    kputs(K_INFO, BANNER);
}

struct thread_tcb thread1;
struct thread_tcb thread2;
struct thread_tcb thread3;

void kernel_main(
        uint32_t hart_id,
		void* config,
		bool use_dev_tree,
		KernelLinkerConfig linker_config) {
    PlatformInfo info;
    print_banner();
    sys_set_core_id(hart_id);
    info.core_id = hart_id;
    struct sbiret impl_id = sbi_relay_get_impl_id();
    struct sbiret march_id = sbi_relay_get_marchid();
    struct sbiret vendor_id = sbi_relay_get_mvendorid();
    kprintf(K_INFO,
            "system: running on core %d | march_id = %d "
            "| vendor_id = %d | impl_id = %d\n", hart_id,
            march_id.value, vendor_id.value, impl_id.value);
    // for now map 132 MiB
    uint32_t identity_map_size = (0x1 << 22U) * 8;
    // map 8 MiB for kernel area initially
    kputs(K_INFO, "system: setting up supervisor level interrupts..\n");
    setup_trap_handlers();
    sys_enable_supervisor_interrupts();
    sys_enable_supervisor_timer_interrupts();
    sys_enable_supervisor_software_interrupts();
    uint32_t higher_half_map_size = identity_map_size / 2;
    kputs(K_INFO,
          "system: setting up early kernel address space.\n");
    create_early_identity_map(linker_config.firmware_load_address,
                              identity_map_size);
    //map_device_tree_area((rvu_word)config);
    kputs(K_INFO, "system: loading memory config from device tree..\n");
    uint64_t mem_range = memory_range_from_device_tree(config);
    uint32_t mem_base = mem_range >> 32;
    uint32_t mem_size = UINT32_MAX & mem_range;
    info.mem_base = mem_base;
    info.mem_size = mem_size;
    pf_bitmap_init(mem_base, mem_size);
    kputs(K_INFO, "system: setting up frame bitmap...\n");
    pf_bitmap_process_linker_config(&linker_config);
    kprintf(K_INFO, "boot: setting up higher half of address space...\n");
    mem_setup_page_table(&linker_config);
    kputs(K_INFO, "system: setting up page frame allocator...\n");
    simple_falloc_init_from_frame_bitmap(mem_base, mem_size);
    mem_set_kernel_virtual_start_address(linker_config.kernel_virtual_base);
    // TODO: make heap setup flexible
    uint32_t kheap_size = (0x1U << 20U); // 1MiB
    uint32_t kheap_start = linker_config.kernel_virtual_base +
            higher_half_map_size - kheap_size;
    // aligned address
    kheap_start = (kheap_start >> 12) << 12;
    kprintf(K_INFO, "system: setting heap @ %p | size = %u bytes\n",
            kheap_start, kheap_size);
    setup_kernel_heap(kheap_start, kheap_size);
    init_malloc((void*)kheap_start, kheap_size);
    kputs(K_INFO, "system: initializing scheduler\n");
    sched_init();
    kputs(K_INFO, "system: setting up system calls\n");
    syscall_setup_table();
    kputs(K_INFO, "system: starting first thread\n");
    sys_set_platform_info(&info);
    sched_init_thread(&thread1, thread_terminal_thread);
    sched_init_thread(&thread2, thread_uart_reader);
    //sched_init_thread(&thread3, thread_transient_task);
    sched_enqueue(&thread1);
    sched_enqueue(&thread2);
    //sched_enqueue(&thread3);
    time_capture_boot_time();
    time_schedule_next_timer(TIMER_TICK_INTERVAL);
    // at this point we either jump to another thread
    // or just wait for the timer interrupt to fire
    while (true) {
        continue;
    }
}

