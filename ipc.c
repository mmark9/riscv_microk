#include "ipc.h"
#include "utils.h"
#include "sched.h"
#include "system.h"
#include "kprint.h"

#include <stdint.h>

struct ipc_msg_buffer ipc_buffers[NUM_TEST_QUEUES];

void ipc_init_msg_buffer(struct ipc_msg_buffer* buffer) {
    sys_kassert(buffer != 0);
    buffer->read_ptr = 0;
    buffer->write_ptr = 0;
}

bool ipc_msg_buffer_full(struct ipc_msg_buffer* buffer) {
    return buffer->count == IPC_BUFFER_SIZE;
}

bool ipc_msg_buffer_empty(struct ipc_msg_buffer* buffer) {
    return buffer->count == 0;
}

void ipc_push_msg(struct ipc_msg* msg, struct ipc_msg_buffer* buffer) {
    sys_kassert(!ipc_msg_buffer_full(buffer));
    uint32_t w_index = buffer->write_ptr;
    buffer->buf[w_index].dest = msg->dest;
    buffer->buf[w_index].src = msg->src;
    kmemcpy(&buffer->buf[w_index].data, &msg->data, IPC_MSG_WORD_SIZE);
    buffer->count += 1;
    buffer->write_ptr = (w_index + 1) % IPC_BUFFER_SIZE;;
}

struct ipc_msg* ipc_pop_msg(struct ipc_msg_buffer* buffer) {
    sys_kassert(!ipc_msg_buffer_empty(buffer));
    uint32_t r_index = buffer->read_ptr;
    buffer->count -= 1;
    buffer->read_ptr = (buffer->read_ptr + 1) % IPC_BUFFER_SIZE;
    return &buffer->buf[r_index];
}

struct ipc_msg_buffer* ipc_map_dst_buffer(uint32_t pid) {
    // TODO: map buffer to address space of sending process
    sys_kassert(pid < NUM_TEST_QUEUES);
    return &ipc_buffers[pid];
}

void ipc_unmap_dst_buffer() {
    // TODO: unmap buffer from address space
}

void ipc_enqueue_wait_write(uint32_t dest_thread) {
    struct thread_tcb* tcb = sched_lookup_thread(dest_thread);
    sys_kassert(tcb != 0);
    tcb->send_queue.count += 1;
    if (tcb->send_queue.head == 0) {
        tcb->send_queue.head = current_thread;
        current_thread->next_snd = current_thread;
        current_thread->prev_snd = current_thread;
        tcb->send_queue.tail = current_thread;
    } else {
        tcb->send_queue.tail->next_snd = current_thread;
        current_thread->next_snd = tcb->send_queue.head;
        current_thread->prev_snd = tcb->send_queue.tail;
        tcb->send_queue.head->next_snd = current_thread;
        tcb->send_queue.tail = current_thread;
    }
}

bool ipc_wait_write_exists(uint32_t snd_thread, uint32_t dest_thread) {
    struct thread_tcb* tcb = sched_lookup_thread(dest_thread);
    sys_kassert(tcb != 0);
    struct thread_tcb* ptr = tcb->send_queue.head;
    uint32_t visit_count = 0;
    while (visit_count <= tcb->send_queue.count) {
        if (ptr->thread_id == snd_thread) {
            return true;
        }
        ptr = ptr->next_snd;
        visit_count += 1;
    }
    return false;
}

struct thread_tcb* ipc_dequeue_wait_write(uint32_t dest_thread) {
    struct thread_tcb* tcb = sched_lookup_thread(dest_thread);
    sys_kassert(tcb != 0);
    if (tcb->send_queue.head == 0) {
        kprintf(K_DEBUG, "ipc [dequeue]: no waiting writing "
                "threads found for dest thread %u\n", dest_thread);
        // we don't treat this as an error
        return 0;
    }
    tcb->send_queue.count -= 1;
    struct thread_tcb* top = tcb->send_queue.head;
    if (tcb->send_queue.count == 0) {
        tcb->send_queue.head = 0;
        tcb->send_queue.tail = 0;
    } else {
        tcb->send_queue.head = tcb->send_queue.head->next_snd;
        tcb->send_queue.head->prev_snd = tcb->send_queue.tail;
        tcb->send_queue.tail->next_snd = tcb->send_queue.head;
    }
    top->next_snd = 0;
    top->prev_snd = 0;
    return top;
}


rvi_word ipc_send_async_msg(const RiscvGPRS* regs, rvu_word sepc) {
    struct ipc_msg_buffer* tmp_buf;
    struct ipc_msg* msg = (struct ipc_msg*)regs->x10_a0;
    tmp_buf = ipc_map_dst_buffer(msg->dest);
    sys_kassert(tmp_buf != 0);
    while (ipc_msg_buffer_full(tmp_buf)) {
        kprintf(K_DEBUG, "ipc [send]: thread %u msg queue full\n", msg->dest);
        kprintf(K_DEBUG, "ipc [send]: sending thread %u is now blocked\n",
                current_thread->thread_id);
        // place in waiting queue before sending msg
        // block process (this is a scheduler operation)
        ipc_enqueue_wait_write(msg->dest);
        // save kernel thread context
        context_save_imm_thread_context(
                current_thread->kernel_context,
                &&IPC_SEND_CONT)
        sched_block_thread(regs, sepc);
        IPC_SEND_CONT:;
        // if we were blocked then SPP will be set to 0
        // at this point. This will cause a privilege
        // switch to the user level which is not what we want
        // so we manually set SPP after this point
        // TODO: find a way to minimize calls to this
        sys_prepare_switch_to_supervisor();
    }
    ipc_push_msg(msg, tmp_buf);
    // check if a thread was waiting for a message
    if (sched_thread_is_blocked(msg->dest)) {
        kprintf(K_DEBUG,
                "ipc [send]: awakening blocked thread %d\n", msg->dest);
        sched_unblock_thread(msg->dest);
    }
    ipc_unmap_dst_buffer();
    return 0;
}

rvi_word ipc_async_recv_msg(const RiscvGPRS* regs, rvu_word sepc) {
    struct ipc_msg* msg_out = (struct ipc_msg*)regs->x10_a0;
    struct ipc_msg_buffer* buf = &ipc_buffers[current_thread->thread_id];
    sys_kassert(buf != 0);
    if (buf->count == 0) {
        kprintf(K_DEBUG,
                "ipc [recv]: thread %u is blocked due to empty msg queue\n",
                current_thread->thread_id);
        context_save_imm_thread_context(
                current_thread->kernel_context,
                &&IPC_RECV_CONT)
        sched_block_thread(regs, sepc);
        IPC_RECV_CONT:;
    }
    // if we were blocked then SPP will be set to 0
    // at this point. This will cause a privilege
    // switch to the user level which is not what we want
    // so we manually set SPP after this point
    // TODO: find a way to minimize calls to this
    sys_prepare_switch_to_supervisor();
    if (msg_out == 0) {
        kputs(K_DEBUG,
              "ipc [recv]: null pointer passed as recv_addr\n");
        return -1;
    }
    struct ipc_msg* msg = ipc_pop_msg(buf);
    kmemcpy((void*)msg_out, (void*)msg, sizeof(struct ipc_msg));
    if (current_thread->send_queue.count > 0) {
        kprintf(K_DEBUG,
                "ipc [recv]: thread %u waking up %d blocked sending threads\n",
                current_thread->thread_id, current_thread->send_queue.count);
        struct thread_tcb* tmp_tcb = 0;
        while (current_thread->send_queue.count > 0) {
            tmp_tcb = ipc_dequeue_wait_write(current_thread->thread_id);
            kprintf(K_DEBUG,
                    "ipc [recv]: thread %u waking up blocked thread %u\n",
                    current_thread->thread_id, tmp_tcb->thread_id);
            sched_unblock_thread(tmp_tcb->thread_id);
        }
    }
    return 0;
}




