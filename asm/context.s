.section .text

.globl load_context
load_context:
    # a0 = RegisterGroup
    lw ra, 4(a0)
    # lw sp, 8(a0)
    lw gp, 12(a0)
    lw tp, 16(a0)
    lw t0, 20(a0)
    lw t1, 24(a0)
    lw t2, 28(a0)
    lw s0, 32(a0)
    lw s1, 36(a0)
    # lw a0, 40(a0)
    lw a1, 40(a0)
    lw a2, 44(a0)
    lw a3, 48(a0)
    lw a4, 52(a0)
    lw a5, 56(a0)
    lw a6, 60(a0)
    lw a7, 64(a0)
    lw s2, 68(a0)
    lw s3, 72(a0)
    lw s4, 76(a0)
    lw s5, 80(a0)
    lw s6, 84(a0)
    lw s7, 88(a0)
    lw s8, 92(a0)
    lw s9, 96(a0)
    lw s10, 100(a0)
    lw s11, 104(a0)
    lw t3, 108(a0)
    lw t4, 112(a0)
    lw t5, 116(a0)
    lw t6, 120(a0)
    addi sp, sp, -8
    sw t0, 0(sp)
    lw t0, 0(a0)
    # set the pc
    csrw sepc, t0
    lw t0, 0(sp)
    # point of no return
    lw a0, 40(a0)
    sret
