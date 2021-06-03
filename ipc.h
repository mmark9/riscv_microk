#ifndef RISCV_MICROK_IPC_H
#define RISCV_MICROK_IPC_H

#include "context.h"

#include <stdint.h>
#include <stdbool.h>

#define NUM_TEST_QUEUES 16
#define IPC_BUFFER_SIZE 4
#define IPC_MSG_WORD_SIZE 64


typedef struct ipc_msg {
    uint32_t src;
    uint32_t dest;
    uint32_t data[IPC_MSG_WORD_SIZE];
} IPCMessage;

// FIFO buffer
typedef struct ipc_msg_buffer {
    uint32_t write_ptr;
    uint32_t read_ptr;
    uint32_t count;
    struct ipc_msg buf[IPC_BUFFER_SIZE];
} IPCMsgBuffer;

void ipc_init_msg_buffer(struct ipc_msg_buffer* buffer);
bool ipc_msg_buffer_full(struct ipc_msg_buffer* buffer);
bool ipc_msg_buffer_empty(struct ipc_msg_buffer* buffer);
void ipc_push_msg(struct ipc_msg* msg, struct ipc_msg_buffer* buffer);
struct ipc_msg* ipc_pop_msg(struct ipc_msg_buffer* buffer);
struct ipc_msg_buffer* ipc_map_dst_buffer(uint32_t pid);
void ipc_enqueue_wait_write(uint32_t dest_thread);
bool ipc_wait_write_exists(uint32_t snd_thread, uint32_t dest_thread);
struct thread_tcb* ipc_dequeue_wait_write(uint32_t dest_thread);
int32_t ipc_send_async_msg(const RiscvGPRS* rges, uint32_t sepc);
int32_t ipc_async_recv_msg(const RiscvGPRS* regs, uint32_t sepc);

#endif //RISCV_MICROK_IPC_H
