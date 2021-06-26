#include "time.h"
#include "kprint.h"
#include "sched.h"
#include "system.h"
#include "terminal.h"
#include "syscalls.h"
#include "sbi_relay.h"

#define TERMINAL_THREAD_ID 0
#define LINE_BUFFER_SIZE 512

// Commands:
// uptime
// messageofday
// shutdown
// dumpmachine
// hostname
// bgas_send_data "message" node 0


typedef enum {
    TERM_UPTIME,
    TERM_SHUTDOWN,
    TERM_HW_INFO,
    TERM_UNKNOWN,
} TerminalCommands;

const char* terminal_cmd_str_map[3] = {"uptime", "shutdown", "cpuinfo"};

int terminal_strcmnp(const char* a, const char* b) {
    while (*a != 0  && *b != 0) {
        if (*a < *b)
            return -1;
        if (*a > *b)
            return 1;
        a++;
        b++;
    }
    return 0;
}

const char* terminal_prompt = "[ascslab@trireme simulation]$ ";

char line_buffer[LINE_BUFFER_SIZE];
uint32_t line_buffer_pos = 0;


TerminalCommands terminal_parse_command(const char* buffer) {
    if (terminal_strcmnp(buffer, terminal_cmd_str_map[TERM_UPTIME]) == 0)
        return TERM_UPTIME;
    else if (terminal_strcmnp(buffer, terminal_cmd_str_map[TERM_SHUTDOWN]) == 0)
        return TERM_SHUTDOWN;
    else if (terminal_strcmnp(buffer, terminal_cmd_str_map[TERM_HW_INFO]) == 0)
        return TERM_HW_INFO;
    else
        return TERM_UNKNOWN;
}

void terminal_interpret_command(const char* line) {
    TerminalCommands cmd = terminal_parse_command(line);
    if (cmd == TERM_UNKNOWN) {
        terminal_printf("shell: unknown command \"%s\"\n", line_buffer);
        terminal_puts(terminal_prompt);
    } else if (cmd == TERM_UPTIME) {
        uint32_t seconds_up = time_secs_since_boot();
        uint32_t minutes = seconds_up / 60;
        uint32_t hours = minutes / 60;
        uint32_t days = hours / 24;
        terminal_printf("  up %d day(s) %d hour(s) %d minute(s) %d second(s)\n",
                        days, hours, minutes, seconds_up);
        terminal_puts(terminal_prompt);
    } else if (cmd == TERM_SHUTDOWN) {
        terminal_puts("shutting down\n");
        sys_shutdown();
    }
}

void terminal_display_character(int ch) {
    if (ch == '\r' || ch == '\n') {
        terminal_putchar('\n');
        terminal_puts(terminal_prompt);
    } else if (ch == 127) {
        terminal_BS();
    } else {
        terminal_putchar(ch);
    }
}

bool enter_key_pressed(int ch) {
    return ch == '\r' || ch == '\n';
}

bool is_display_character(int ch) {
    return ch >= 0x20 && ch <= 0x7E;
}

void thread_terminal_thread() {
    terminal_clear();
    terminal_puts(terminal_prompt);
    struct ipc_msg msg;
    int32_t ipc_res = 0;
    int32_t output_char = 0;
    while (true) {
        ipc_res = sys_do_ipc_recv_async(&msg);
        if (ipc_res == 0) {
            output_char = msg.data[0];
            if (is_display_character(output_char)) {
                terminal_putchar(output_char);
                if (line_buffer_pos >= LINE_BUFFER_SIZE)
                    sys_panic("terminal line buffer is full!\n");
                line_buffer[line_buffer_pos++] = output_char;
            } else if (enter_key_pressed(output_char)) {
                line_buffer[line_buffer_pos] = 0;
                line_buffer_pos = 0;
                terminal_putchar('\n');
                terminal_interpret_command(line_buffer);
            } else {
                // interpret control character
            }
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
    uint32_t msec_delta = 0;
    uint32_t read_interval_msec = 200;
    out_msg.src = current_thread->thread_id;
    out_msg.dest = TERMINAL_THREAD_ID;
    while (true) {
        elapsed = time_msecs_since_boot();
        msec_delta = elapsed - old_elapsed;
        if (msec_delta > read_interval_msec) {
            old_elapsed = elapsed;
            out_msg.data[0] = long_msg[msg_index];
            msg_index = (msg_index + 1) % msg_len;
            ipc_res = sys_do_ipc_send_async(&out_msg);
            sys_kassert(ipc_res == 0);
        }
    }
}

void thread_uart_reader() {
    int32_t ipc_res = 0;
    struct ipc_msg out_msg;
    uint32_t elapsed = 0;
    uint32_t old_elapsed = 0;
    uint32_t msec_delta = 0;
    uint32_t read_interval_msec = 200;
    out_msg.src = current_thread->thread_id;
    out_msg.dest = TERMINAL_THREAD_ID;
    int in_ch = 0;
    while (true) {
        elapsed = time_msecs_since_boot();
        msec_delta = elapsed - old_elapsed;
        in_ch = sbi_relay_console_getchar();
        if (in_ch == -1)
            continue;
        out_msg.data[0] = in_ch;
        ipc_res = sys_do_ipc_send_async(&out_msg);
    }
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
        /*if (elapsed % 50 == 0 && elapsed > 0)
            sys_do_yield();*/
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
        /*if (elapsed % 100 == 0 && elapsed > 0 )
            sys_do_yield();*/
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