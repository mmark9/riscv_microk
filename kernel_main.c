#include "sched.h"
#include "kprint.h"
#include "system.h"
#include "interrupt.h"
#include "sbi_relay.h"
#include "constants.h"
#include "utils.h"
#include "time.h"
#include "memory.h"
#include "syscalls.h"
#include "simple_falloc.h"
#include "page_frame.h"
#include "terminal.h"

#include <stdint.h>
#include <stdbool.h>

const char* BANNER = " _____ ___  ___ ___ ___  __   __  _  _____ ___ _  _ ___ _    \n"
                     " |_   _| _ \\/ __|_ _/ __|_\\ \\ / / | |/ / __| _ \\ \\| | __| |   \n"
                     "   | | |   /\\__ \\| | (_|___\\ V /  | ' <| _||   / .` | _|| |__ \n"
                     "   |_| |_|_\\|___/___\\___|   \\_/   |_|\\_\\___|_|_\\_|\\_|___|____|\n"
                     "                                                              \n";

void print_banner() {
    kputs(K_INFO, "\n\n");
    kputs(K_INFO, BANNER);
}

void thread_func1() {
    for (uint32_t i = 0; i < 40; i++) {
        kprintf(K_INFO,
                "thread %d: executing iteration %d...\n",
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
        kprintf(K_INFO,
                "thread %d: executing iteration %d...\n",
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
    uint32_t uptime = 0;
    for (uint32_t i = 0;; i++) {
        uptime = time_secs_since_boot();
        if (uptime % 3 == 0 && uptime > 0) {
            kprintf(K_INFO,
                    "thread %d: executing "
                    "preemptive thread (iter: %d)...\n",
                    current_thread->thread_id, i);
            accumulator += i;
        }
        if (uptime % 9 == 0) {
            kprintf(K_INFO,
                    "thread %d: preemptive thread yielding (iter: %d)...\n",
                    current_thread->thread_id, i);
            sys_do_yield();
        }
    }
}

void thread_func4() {
    uint32_t accumulator = 0;
    uint32_t uptime = 0;
    for (uint32_t i = 0;; i++) {
        uptime = time_secs_since_boot();
        if (uptime % 7 == 0 && uptime > 0) {
            kprintf(K_INFO,
                    "thread %d: exiting "
                    "preemptive thread (iter: %d)...\n",
                    current_thread->thread_id, i);
            accumulator += i;
            sys_do_exit(1);
        }
    }
}

void thread_ipc_send_func() {
    int32_t ipc_res = 0;
    struct ipc_msg out_msg;
    uint32_t elapsed = 0;
    out_msg.src = current_thread->thread_id;
    while (true) {
        elapsed = time_secs_since_boot();
        out_msg.data[0] = time_msecs_since_boot() + 0xDE;
        out_msg.dest = 2;
        kprintf(K_INFO, "thread %d: send msg %u to thread %d\n",
                current_thread->thread_id, out_msg.data[0], out_msg.dest);
        ipc_res = sys_do_ipc_send_async(&out_msg);
        if (elapsed % 50 == 0 && elapsed > 0)
            sys_do_yield();
    }
}

void thread_ipc_recv_func() {
    int32_t ipc_res = 0;
    struct ipc_msg msg;
    uint32_t elapsed = 0;
    while (true) {
        ipc_res = sys_do_ipc_recv_async(&msg);
        if (ipc_res == 0) {
            kprintf(K_INFO,
                    "thread %d: received msg %u from thread %d\n",
                    current_thread->thread_id, msg.data[0], msg.src);
        }
        if (elapsed % 100 == 0 && elapsed > 0 )
            sys_do_yield();
    }
}

void thread_ipc_func() {
    int32_t ipc_res = 0;
    struct ipc_msg msg;
    struct ipc_msg out_msg;
    out_msg.src = current_thread->thread_id;
    while (true) {
        out_msg.data[0] = 0xDEADBEEF + time_secs_since_boot();
        out_msg.dest = time_msecs_since_boot() % 2;
        sys_do_ipc_send_async(&out_msg);
        if (time_secs_since_boot() % 5 == 0)
            sys_do_yield();
        ipc_res = sys_do_ipc_recv_async(&msg);
        if (ipc_res == 0) {
            kprintf(K_INFO,
                    "thread %d: received msg from thread %d\n",
                    current_thread->thread_id, msg.src);
        }
        sys_do_yield();
    }
}

struct thread_tcb thread1;
struct thread_tcb thread2;
struct thread_tcb thread3;

#define TERMINAL_THREAD_ID 0

void thread_terminal_thread() {
    const char* terminal_prompt = "[ascslab@trireme simulation]$ ";
    //terminal_ed(CLEAR_ENTIRE_SCREEN);
    terminal_clear();
    terminal_puts(terminal_prompt);
    struct ipc_msg msg;
    int32_t ipc_res = 0;
    int32_t output_char = 0;
    while (true) {
        ipc_res = sys_do_ipc_recv_async(&msg);
        if (ipc_res == 0) {
            output_char = msg.data[0];
            terminal_putchar(output_char);
            if (output_char == '\n')
                terminal_puts(terminal_prompt);
        }
    }
}

void thread_uart_character_reader() {
    int32_t ipc_res = 0;
    struct ipc_msg out_msg;
    uint32_t elapsed = 0;
    uint32_t msg_index = 0;
    const char* long_msg = "Sending test command.......\n";
    uint32_t msg_len = kstrlen(long_msg);
    uint32_t old_elapsed = 0;
    out_msg.src = current_thread->thread_id;
    out_msg.dest = TERMINAL_THREAD_ID;
    while (true) {
        elapsed = time_secs_since_boot();
        if (old_elapsed != elapsed) {
            old_elapsed = elapsed;
            out_msg.data[0] = long_msg[msg_index];
            msg_index = (msg_index + 1) % msg_len;
            ipc_res = sys_do_ipc_send_async(&out_msg);
            sys_kassert(ipc_res == 0);
        }
    }
}

void kernel_main(
        uint32_t hart_id,
		void* config,
		bool use_dev_tree,
		KernelLinkerConfig linker_config) {
    print_banner();
    sys_set_core_id(hart_id);
    struct sbiret impl_id = sbi_relay_get_impl_id();
    struct sbiret march_id = sbi_relay_get_marchid();
    struct sbiret vendor_id = sbi_relay_get_mvendorid();
    kprintf(K_INFO,
            "system: running on core %d | march_id = %d "
            "| vendor_id = %d | impl_id = %d\n", hart_id,
            march_id.value, vendor_id.value, impl_id.value);
    kprintf(K_INFO,
            "boot: kernel image size %d\n", linker_config.kernel_size_in_bytes);
    // for now map 16 MiB
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
    map_device_tree_area((uint32_t)config);
    kputs(K_INFO, "system: loading memory config from device tree..\n");
    uint64_t mem_range = memory_range_from_device_tree(config);
    uint32_t mem_base = mem_range >> 32;
    uint32_t mem_size = UINT32_MAX & mem_range;
    kprintf(K_INFO,
            "system: memory_start = %p | memory_size = %u\n",
            mem_base, mem_size);
    kputs(K_INFO, "system: setting up frame bitmap...\n");
    init_frame_bitmap_from_linker_config(&linker_config);
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
    kputs(K_INFO, "system: initializing scheduler\n");
    sched_init();
    kputs(K_INFO, "system: setting up system calls\n");
    syscall_setup_table();
    kputs(K_INFO, "system: starting first thread\n");
    sched_init_thread(&thread1, thread_terminal_thread);
    sched_init_thread(&thread2, thread_uart_character_reader);
    //sched_init_thread(&thread3, thread_ipc_recv_func);
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

