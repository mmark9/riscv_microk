# This is the official start of the kernel
# Expected enviornment:
# a0 = boot core id
# a1 = configuration data
# a2 = config type: 0 = config string | 1 = device tree
# a3 = load address
# a4 = linker_load_config

.section .bss
.align 0x10
kernel_stack_top:
.skip 0x4000
kernel_stack_bottom:

.align 0x2
.section .text
.globl kernel_boot
kernel_boot:
    # setup supervisor trap handler
    # set trap vector to supervisor handler
	# should we disable interrupts here?
	li t4,0x2
	csrc sstatus,t4
	la t4, supervisor_trap
    csrw stvec,t4
	# set up stack
	# TODO: avoid hard coding
	li a1, 0x87000000
	la sp,kernel_stack_bottom
	# call main
	call kernel_main
halt:
	j halt

.align 0x2
.globl halt_system
halt_system:
    nop
    nop
    j halt_system