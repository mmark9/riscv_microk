.align 0x2
.globl supervisor_trap
.section .text
supervisor_trap:
    # if not task is associated
    # with this thread then simply
    # use current context
    beqz tp,push_context
    # save registers in scratch area
    sd gp,8(tp)
    sd t0,16(tp)
    # load context level
    ld gp,24(tp)
    addi gp,gp,1
    sd gp,24(tp)
    # save t0 in scratch area
    li t0,2
    bge gp,t0,restore_scratch
sditch_to_kernel_stack:
    # we need to sditch to kernel stack
    sd sp,32(tp)
    ld sp,40(tp)
restore_scratch:
    ld gp,8(tp)
    ld t0,16(tp)
push_context:
    addi sp,sp,-232
    sd ra,0(sp)
    # skip sp
    sd t0,16(sp)
    sd t1,24(sp)
    sd t2,32(sp)
    sd s0,40(sp)
    sd s1,48(sp)
    sd a0,56(sp)
    sd a1,64(sp)
    sd a2,72(sp)
    sd a3,80(sp)
    sd a4,88(sp)
    sd a5,96(sp)
    sd a6,104(sp)
    sd a7,112(sp)
    sd s2,120(sp)
    sd s3,128(sp)
    sd s4,136(sp)
    sd s5,144(sp)
    sd s6,152(sp)
    sd s7,160(sp)
    sd s8,168(sp)
    sd s9,176(sp)
    sd s10,184(sp)
    sd s11,192(sp)
    sd t3,200(sp)
    sd t4,208(sp)
    sd t5,216(sp)
    sd t6,224(sp)
    # TODO: make this more efficient
    # store user stack in regs structure
    beqz tp,call_handler
    ld a0,32(tp)
    sd a0,8(sp)
call_handler:
    mv a0,sp
    # at this point we should sditch stacks
    call supervisor_handle_trap
return_from_trap_handler:
    ld ra,0(sp)
    ld t0,16(sp)
    ld t1,24(sp)
    ld t2,32(sp)
    ld s0,40(sp)
    ld s1,48(sp)
    ld a0,56(sp)
    ld a1,64(sp)
    ld a2,72(sp)
    ld a3,80(sp)
    ld a4,88(sp)
    ld a5,96(sp)
    ld a6,104(sp)
    ld a7,112(sp)
    ld s2,120(sp)
    ld s3,128(sp)
    ld s4,136(sp)
    ld s5,144(sp)
    ld s6,152(sp)
    ld s7,160(sp)
    ld s8,168(sp)
    ld s9,172(sp)
    ld s10,184(sp)
    ld s11,192(sp)
    ld t3,208(sp)
    ld t4,208(sp)
    ld t5,216(sp)
    ld t6,224(sp)
    addi sp,sp,232
check_context_level:
    beqz tp,ret_from_interrupt
    sd gp,8(tp)
    # load context level
    ld gp,24(tp)
    addi gp,gp,-1
    sd gp,24(tp)
    bgtz gp,ret_from_interrupt
    # load sp for user
    ld sp,32(tp)
ret_from_interrupt:
    sret