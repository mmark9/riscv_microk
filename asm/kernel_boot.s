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
	la t4, supervisor_trap
    csrw stvec, t4
    li t4, 34
    csrw sie, t4
	# set up stack
	la sp, kernel_stack_bottom
	# call main
	call kernel_main
halt:
	j halt

supervisor_trap:
    # mask out the current interrupt
    csrr t0, sstatus
	csrr t1, scause
	csrr t2, sbadaddr
    call supervisor_handle_interrupt
    csrw sepc, a0 # a0 stores the next pc
    sret

.globl halt_system
halt_system:
    nop
    nop
    j halt_system