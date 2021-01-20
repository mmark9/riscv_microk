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

.section .text
.globl kernel_boot
kernel_boot:
    # setup supercisor trap handler
    # set trap vector to supervisor handler
	# should we disable interrupts here?
	la t4, supervisor_handle_interrupt
    csrw stvec, t4
	# set up stack
	la sp, kernel_stack_bottom
	# call main
	call kernel_main
halt:
	j halt

supervisor_trap:
    csrr t0, mstatus
	csrr t1, mcause
	csrr t2, mbadaddr
    call supervisor_handle_interrupt
    mret