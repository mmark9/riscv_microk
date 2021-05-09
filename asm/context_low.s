.section .text

.globl load_context
load_context:
    # a0 = RegisterGroup
    # at this point the sp needs to be re-adjusted
    mv tp, a0
    lw sp,0(a0)
    lw tp,4(a0)
    lw t0,8(a0)
    lw t1,12(a0)
    lw t2,16(a0)
    lw s0,20(a0)
    lw s1,24(a0)
    lw a0,28(a0)
    lw a1,32(a0)
    lw a2,36(a0)
    lw a3,40(a0)
    lw a4,44(a0)
    lw a5,48(a0)
    lw a6,52(a0)
    lw a7,56(a0)
    lw s2,60(a0)
    lw s3,64(a0)
    lw s4,68(a0)
    lw s5,72(a0)
    lw s6,76(a0)
    lw s7,80(a0)
    lw s8,84(a0)
    lw s9,88(a0)
    lw s10,92(a0)
    lw s11,96(a0)
    lw t3,100(a0)
    lw t4,104(a0)
    lw t5,108(a0)
    lw t6,112(a0)
    # TODO: check if we need to switch the address space
    # point of no return
    sret