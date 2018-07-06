.section .bss
.align 0x10
kernel_stack_top: 
.skip 16384
kernel_stack_bottom:	

.section .text
.equ RTC_BASE,      0x40000000
.equ TIMER_BASE,    0x40004000

.global _entry
_entry:
	# Boot fence; we should land here first
	addi zero, zero, 0
	addi zero, zero, 0
	addi zero, zero, 0
	addi zero, zero, 0
	addi zero, zero, 0
clear_regs:
	xori t0, t0, 0
	xori t1, t1, 0
	xori t2, t2, 0
	xori t3, t3, 0
	xori t4, t4, 0
	xori t5, t5, 0
	xori t6, t6, 0
	xori a0, a0, 0
	xori a1, a1, 0
	xori a2, a2, 0
	xori a3, a3, 0
	xori a4, a4, 0
	xori a5, a5, 0
	xori a6, a6, 0
	xori a7, a7, 0
	xori s0, s0, 0
	xori s1, s1, 0
	xori s2, s2, 0
	xori s3, s3, 0
	xori s4, s4, 0
	xori s5, s5, 0
	xori s6, s6, 0
	xori s7, s7, 0
	xori s8, s8, 0
	xori s9, s9, 0
	xori s10, s10, 0
	xori s11, s11, 0
	xori ra, ra, 0
	xori gp, gp, 0
	xori tp, tp, 0
kernel_prep:
	# set up stack
	la sp, kernel_stack_bottom
	# call main
	call riscv_main
	# setup paging?
halt:
	j halt
	addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0

.align 0x4
.global asm_machine_trap
asm_machine_trap:
	# t0 = mcause
	# t1 = is_interrupt | 1 = yes / 0 = no
	# t2 = exception code
	csrr t6, mstatus # debugging
	csrr t0, mcause
	srli t1, t0, 31
	slli t2, t0, 1
	srli t2, t2, 1

	# branch on sign bit
	beqz t1, handle_machine_exception
handle_machine_interrupt:
	call riscv_handle_machine_interrupt
	csrr t0, mepc
	srli t0, t0, 1
	addi t0, t0, 4
	slli t0, t0, 1
	csrw mepc, t0
	mret
handle_machine_exception:
	li t3, 11
	beq t2, t3, jump_to_supervisor
	call riscv_handle_machine_interrupt
	# restore regs
	mret
jump_to_supervisor:
	# clear MPP
	li t5, 3
	slli t5, t5, 11
	csrc mstatus, t5
	# set MPP in mstatus to 1 for supervisor switch
	li t5, 1
	slli t5, t5, 11
	csrs mstatus, t5
	# set jump to first supervisor routine
	la t4, riscv_supervisor_mode_do_setup
	csrw mepc, t4
	mret


.align 0x4
.global asm_supervisor_trap
asm_supervisor_trap:
	call riscv_handle_supervisor_interrupt
	# TODO: eventually we should check xPP field to
	# return to the correct privilege level (USER | SUPERVISOR)
	sret
