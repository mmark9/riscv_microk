.section .text

.globl load_context
load_context:
    # a0 = RegisterGroup
    # at this point the sp needs to be re-adjusted
    ld ra,0(a0)
    ld sp,8(a0)
    ld t0,16(a0)
    ld t1,24(a0)
    ld t2,32(a0)
    ld s0,40(a0)
    ld s1,48(a0)
    ld a1,56(a0)
    ld a2,64(a0)
    ld a3,72(a0)
    ld a4,80(a0)
    ld a5,88(a0)
    ld a6,96(a0)
    ld a7,104(a0)
    ld s2,112(a0)
    ld s3,120(a0)
    ld s4,128(a0)
    ld s5,136(a0)
    ld s6,144(a0)
    ld s7,152(a0)
    ld s8,160(a0)
    ld s9,168(a0)
    ld s10,176(a0)
    ld s11,184(a0)
    ld t3,192(a0)
    ld t4,200(a0)
    ld t5,208(a0)
    ld t6,216(a0)
    ld a0,224(a0)
    # TODO: check if we need to switch the address space
    # point of no return
    sret