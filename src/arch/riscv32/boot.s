# 1 "src/arch/riscv32/boot.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "src/arch/riscv32/boot.S"
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
 addi t0, t0, 0
 addi t1, t1, 0
 addi t2, t2, 0
 addi t3, t3, 0
 addi t4, t4, 0
 addi t5, t5, 0
 addi t6, t6, 0
 addi a0, a0, 0
 addi a1, a1, 0
 addi a2, a2, 0
 addi a3, a3, 0
 addi a4, a4, 0
 addi a5, a5, 0
 addi a6, a6, 0
 addi a7, a7, 0
 addi s0, s0, 0
 addi s1, s1, 0
 addi s2, s2, 0
 addi s3, s3, 0
 addi s4, s4, 0
 addi s5, s5, 0
 addi s6, s6, 0
 addi s7, s7, 0
 addi s8, s8, 0
 addi s9, s9, 0
 addi s10, s10, 0
 addi s11, s11, 0
 addi ra, ra, 0
 addi gp, gp, 0
 addi tp, tp, 0
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
