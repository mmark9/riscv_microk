# This is the official start of the kernel
# Expected enviornment:
# a0 = boot core id
# a1 = configuration data
# a2 = config type: 0 = config string | 1 = device tree
# a3 = load address
# a4 = linker_load_config

.section bss
.align 0x4
kernel_stack_top:
.skip 0x4000
kernel_stack_bottom:

.section .text
.globl kernel_boot
kernel_boot:
	# set up stack
	la sp, kernel_stack_bottom
	# call main
	call kernel_main
halt:
	j halt
