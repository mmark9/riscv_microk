.section .bss
.align 0x10
kernel_stack_top: 
.skip 16384
kernel_stack_bottom:	

.section .text
.global _entry
	# Boot fence; we should land here first
	addi zero, zero, 0
	addi zero, zero, 0
	addi zero, zero, 0
	addi zero, zero, 0
	addi zero, zero, 0
_entry:
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
	# set up stack
	la sp, kernel_stack_bottom
	# call main
	call hello_main
	# setup paging?
halt:
	j halt
	addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0
