.section .bss, "aw", @nobits
.align 0x10
fw_stack_top:
.skip 0x4000
fw_stack_bottom:

.align 0x2
.section .text, "ax"
.globl fw_start
fw_start:
    addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0
fw_clear_registers:
    xor ra,ra,ra
    xor sp,sp,sp
    xor gp,gp,gp
    xor tp,tp,tp
    xor t0,t0,t0
    xor t1,t1,t1
    xor t2,t2,t2
    xor s0,s0,s0
    xor s1,s1,s1
    xor a0,a0,a0
    xor a1,a1,a1
    xor a2,a2,a2
    xor a3,a3,a3
    xor a4,a4,a4
    xor a5,a5,a5
    xor a6,a6,a6
    xor a7,a7,a7
    xor s2,s2,s2
    xor s3,s3,s3
    xor s4,s4,s4
    xor s5,s5,s5
    xor s6,s6,s6
    xor s7,s7,s7
    xor s8,s8,s8
    xor s9,s9,s9
    xor s10,s10,s10
    xor s11,s11,s11
    xor t3,t3,t3
    xor t4,t4,t4
    xor t5,t5,t5
    xor t6,t6,t6
fw_trap_setup:
	# delegate all exceptions to supervisor
	# (with the exception of Environment Call from M-mode)
	li t0,0x3BFF
	#csrw medeleg,t0
	# delegate all interrupts to supervisor
	li t0,0xBBB
	#csrw mideleg,t0

	# first set machine trap vector
	# t0 = mtvec buffer; mode set to Direct implicitly
	# NOTE: base address should be aligned on 4 byte boundary!
	la t0,fw_trap

	# copy buffer to mtvec
	csrw mtvec,t0

	# ecalls are non-maskable since they are encoded
	# as illegal instructions; no need to enable interrupts
	# for this to work
fw_jump_to_c_setup:
    la sp, fw_stack_bottom
    jal fw_main_entry

.globl fw_jump_to_kernel
fw_jump_to_kernel:
    # a0 stores next address
	# clear MPP
	li t0, 0x3
	slli t0, t0, 0xb
	csrc mstatus, t0
	# set MPP in mstatus to 1 for supervisor switch
	li t0, 0x1
	slli t0, t0, 0xb
	csrs mstatus, t0
	# set PC to the start of page setup
	mv t1,a0
	#csrw sepc, t1
	csrw mepc, t1
	# prepare arguments
	csrr a0,mhartid
	# TODO: pase a real device tree
	xor a1,a1,a1
	# setup the argument registers
    #csrr a0,mhartid
    li t0, 0xf
    csrw pmpcfg0, t0
    li t0, -1
    csrw pmpaddr0, t0
	mret

.align 0x2
fw_trap:
    csrw mscratch,sp
    la sp,fw_stack_bottom
    addi sp,sp,-232
fw_save_context:
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
    # save old stack pointer
    csrr t0,mscratch
    sd t0,8(sp)
fw_jump_to_handler:
    xor t0,t0,t0
    mv a0,sp
    jal fw_handle_trap
fw_return_from_handler:
    # save original stack
    # pointer into MSCRATCH
    ld a0,8(sp)
    csrw mscratch,a0
    xor a0,a0,a0
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
    # reload original stack
    csrr sp,mscratch
    mret



