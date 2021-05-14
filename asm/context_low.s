.section .text

.globl load_context
load_context:
    # a0 = RegisterGroup
    # at this point the sp needs to be re-adjusted
    mv tp, a0
    lw ra,0(tp)
    lw sp,4(tp)
    lw t0,8(tp)
    lw t1,12(tp)
    lw t2,16(tp)
    lw s0,20(tp)
    lw s1,24(tp)
    lw a0,28(tp)
    lw a1,32(tp)
    lw a2,36(tp)
    lw a3,40(tp)
    lw a4,44(tp)
    lw a5,48(tp)
    lw a6,52(tp)
    lw a7,56(tp)
    lw s2,60(tp)
    lw s3,64(tp)
    lw s4,68(tp)
    lw s5,72(tp)
    lw s6,76(tp)
    lw s7,80(tp)
    lw s8,84(tp)
    lw s9,88(tp)
    lw s10,92(tp)
    lw s11,96(tp)
    lw t3,100(tp)
    lw t4,104(tp)
    lw t5,108(tp)
    lw t6,112(tp)
    # TODO: check if we need to switch the address space
    # point of no return
    sret