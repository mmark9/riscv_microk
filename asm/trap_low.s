.align 0x2
.globl supervisor_trap
.section .text
supervisor_trap:
    # if not task is associated
    # with this thread then simply
    # use current context
    beqz tp,push_context
    # save registers in scratch area
    sw gp,4(tp)
    sw t0,8(tp)
    # load context level
    lw gp,12(tp)
    addi gp,gp,1
    sw gp,12(tp)
    # save t0 in scratch area
    li t0,2
    bge gp,t0,restore_scratch
switch_to_kernel_stack:
    # we need to switch to kernel stack
    sw sp,16(tp)
    lw sp,20(tp)
restore_scratch:
    lw gp,4(tp)
    lw t0,8(tp)
push_context:
    addi sp,sp,-116
    sw ra,0(sp)
    # sw tp,4(sp)
    sw t0,8(sp)
    sw t1,12(sp)
    sw t2,16(sp)
    sw s0,20(sp)
    sw s1,24(sp)
    sw a0,28(sp)
    sw a1,32(sp)
    sw a2,36(sp)
    sw a3,40(sp)
    sw a4,44(sp)
    sw a5,48(sp)
    sw a6,52(sp)
    sw a7,56(sp)
    sw s2,60(sp)
    sw s3,64(sp)
    sw s4,68(sp)
    sw s5,72(sp)
    sw s6,76(sp)
    sw s7,80(sp)
    sw s8,84(sp)
    sw s9,88(sp)
    sw s10,92(sp)
    sw s11,96(sp)
    sw t3,100(sp)
    sw t4,104(sp)
    sw t5,108(sp)
    sw t6,112(sp)
    # TODO: make this more efficient
    # store user stack in regs structure
    beqz tp,call_handler
    lw a0,16(tp)
    sw a0,4(sp)
call_handler:
    mv a0,sp
    # at this point we should switch stacks
    call supervisor_handle_trap
return_from_trap_handler:
    lw ra,0(sp)
    lw t0,8(sp)
    lw t1,12(sp)
    lw t2,16(sp)
    lw s0,20(sp)
    lw s1,24(sp)
    lw a0,28(sp)
    lw a1,32(sp)
    lw a2,36(sp)
    lw a3,40(sp)
    lw a4,44(sp)
    lw a5,48(sp)
    lw a6,52(sp)
    lw a7,56(sp)
    lw s2,60(sp)
    lw s3,64(sp)
    lw s4,68(sp)
    lw s5,72(sp)
    lw s6,76(sp)
    lw s7,80(sp)
    lw s8,84(sp)
    lw s9,88(sp)
    lw s10,92(sp)
    lw s11,96(sp)
    lw t3,100(sp)
    lw t4,104(sp)
    lw t5,108(sp)
    lw t6,112(sp)
    addi sp,sp,116
check_context_level:
    beqz tp,ret_from_interrupt
    sw gp,4(tp)
    # load context level
    lw gp,12(tp)
    addi gp,gp,-1
    sw gp,12(tp)
    bgtz gp,ret_from_interrupt
    # load sp for user
    lw sp,16(tp)
ret_from_interrupt:
    sret