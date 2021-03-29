# This is the official start of the kernel
# Expected enviornment:
# a0 = boot core id
# a1 = configuration data
# a2 = config type: 0 = config string | 1 = device tree
# a3 = load address
# a4 = linker_load_config

.section .bss
.align 0x4
kernel_stack_top:
.skip 0x4000
kernel_stack_bottom:

.align 0x2
.section .text
.globl kernel_boot
kernel_boot:
    # setup supercisor trap handler
    # set trap vector to supervisor handler
	# should we disable interrupts here?
	li t4,0x2
	csrc sstatus,t4
	la t4, supervisor_trap
    csrw stvec,t4
	# set up stack
	la sp,kernel_stack_bottom
	# call main
	call kernel_main
halt:
	j halt

.align 0x2
supervisor_trap:
    addi sp,sp,-128
    sw zero,0x0(sp)
    sw ra,0x4(sp)
    sw sp,0x8(sp)
    sw gp,0xc(sp)
    sw tp,0x10(sp)
    sw t0,0x14(sp)
    sw t1,0x18(sp)
    sw t2,0x1c(sp)
    sw s0,0x20(sp)
    sw s1,0x24(sp)
    sw a0,0x28(sp)
    sw a1,0x2c(sp)
    sw a2,0x30(sp)
    sw a3,0x34(sp)
    sw a4,0x38(sp)
    sw a5,0x3c(sp)
    sw a6,0x40(sp)
    sw a7,0x44(sp)
    sw s2,0x48(sp)
    sw s3,0x4c(sp)
    sw s4,0x50(sp)
    sw s5,0x54(sp)
    sw s6,0x58(sp)
    sw s7,0x5c(sp)
    sw s8,0x60(sp)
    sw s9,0x64(sp)
    sw s10,0x68(sp)
    sw s11,0x6c(sp)
    sw t3,0x70(sp)
    sw t4,0x74(sp)
    sw t5,0x78(sp)
    sw t6,0x7c(sp)
    mv a0,sp
    # at this point we should switch stacks
    call supervisor_handle_trap
    lw ra,0x4(sp)
    lw gp,0x8(sp)
    lw tp,0xc(sp)
    lw t0,0x10(sp)
    lw t1,0x14(sp)
    lw t2,0x18(sp)
    lw s0,0x1c(sp)
    lw s1,0x20(sp)
    lw a0,0x24(sp)
    lw a1,0x28(sp)
    lw a2,0x2c(sp)
    lw a3,0x30(sp)
    lw a4,0x34(sp)
    lw a5,0x38(sp)
    lw a6,0x3c(sp)
    lw a7,0x40(sp)
    lw s2,0x44(sp)
    lw s3,0x48(sp)
    lw s4,0x4c(sp)
    lw s5,0x50(sp)
    lw s6,0x54(sp)
    lw s7,0x58(sp)
    lw s8,0x5c(sp)
    lw s9,0x60(sp)
    lw s10,0x64(sp)
    lw s11,0x68(sp)
    lw t3,0x6c(sp)
    lw t4,0x70(sp)
    lw t5,0x74(sp)
    lw t6,0x78(sp)
    addi sp,sp,128
    sret

.align 0x2
.globl halt_system
halt_system:
    nop
    nop
    j halt_system