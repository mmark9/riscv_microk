# Constants for initial memory configuration
# This is a higher-half kernel that starts at 3.5GB mark
.equ KERNEL_VIRTUAL_BASE, 0xE0000000
.equ VIRTUAL_MEMORY_SIZE, 0xFFFFFFFF
.global KERNEL_LOAD_ADDRESS
.global KERNEL_VIRTUAL_BASE
# Constants set by the linker
.extern KERNEL_VIRTUAL_END
.extern KERNEL_SIZE_IN_BYTES

# 16 kB stack aligned on 2 byte boundary
.section .bss
.align 0x4
kernel_stack_top:
.skip 0x4000
kernel_stack_bottom:

.section .boot_bss, "aw", @nobits
.align 0xC
page_table_1:
    .skip 0x400 * 4, 0x0
page_directory:
    .skip 0x400 * 4, 0x0


# constants for table setup
.equ PAGE_SIZE, 0x1000
.equ LVL2_TABLE_COUNT, 0x1
.equ PAGES_PER_TABLE, 0x400
.equ PAGE_TABLE_SIZE, PAGES_PER_TABLE * PAGE_SIZE
.equ MAX_PTE_COUNT, LVL2_TABLE_COUNT * PAGES_PER_TABLE
.equ MAX_PDE_COUNT, MAX_PTE_COUNT / PAGES_PER_TABLE
.equ KERNEL_PAGE_DIRECTORY_START_INDEX, KERNEL_VIRTUAL_BASE / 0x400000
#.set MAX_PDE_ENTRY_OFFSET, TABLE_COUNT * 4

.section .boot_text, "ax"
.globl boot_entry
boot_entry:
	# Boot fence; we should land here first
	addi zero, zero, 0
	addi zero, zero, 0
	addi zero, zero, 0
	addi zero, zero, 0
	addi zero, zero, 0
	xor t0, t0, t0
	xor t1, t1, t1
	xor t2, t2, t2
	xor t3, t3, t3
	xor t4, t4, t4
	xor t5, t5, t5
	xor t6, t6, t6
	# what board are we on ?
	jal load_riscv_board_config
	# a3 contains the load address
boot_identity_map:
	xor s5, s5, s5
	add s5, s5, a3
	# 4mb
	li t0, 0x400000
	divu s6, a3, t0
	li s7, 0xF
	li s8, 0x1
	li s9, 0x1
	jal lvl1_table_setup
higher_half_map:
	xor s5, s5, s5
	add s5, s5, a3
	li s6, KERNEL_PAGE_DIRECTORY_START_INDEX
	li s7, 0xF
	li s8, 0x1
	li s9, 0x1
	jal lvl1_table_setup
machine_mode_setup:
	# first set machine trap vector
	# t0 = mtvec buffer; mode set to Direct implicitly
	# NOTE: base address should be aligned on 4 byte boundary!
	la t0, jump_to_supervisor

	# copy buffer to mtvec
	csrw mtvec, t0

	# next do minimal software interrupt setup
	# set mie using t0
	xor t0, t0, t0
	# machine + supervisor software enabled
	addi t0, t0, 0xA
	csrw mie, t0

	# set minimum for interupt delegations
	xor t0, t0, t0
	addi t0, t0, 0xA
	csrw mideleg, t0

	# enable machine interrupts
	li t0, 0xA
	csrs mstatus, t0
	ecall
.align 0x2
jump_to_supervisor:
	# reset trapp vector for catching general errors with boot
	la t0, trap_boot_exceptions
	csrw mtvec, t0
	# check status register
	csrr t5, mstatus
	# clear MPP
	li t0, 3
	slli t0, t0, 11
	csrc mstatus, t0
	# set MPP in mstatus to 1 for supervisor switch
	li t0, 1
	slli t0, t0, 11
	csrs mstatus, t0
	# set PC to the start of page setup
	la t1, supervisor_entry
	csrw mepc, t1
	mret
supervisor_entry:
	xor t5, t5, t5
	csrr t5, sstatus
	# setup paging
enable_paging:
	# t0 = used to copy to satp reg
	xor t0, t0, t0
	# Set mode = 1 and ASID = 0
	addi t0, t0, 0x200
	slli t0, t0, 0x16

	# set PPN of page directory (lvl1 table)
	xor t1, t1, t1
	xor t2, t2, t2
	xor t3, t3, t3
	li t1, PAGE_SIZE
	la t2, page_directory
	divu t3, t2, t1

	# set PPN in satp buffer (t3)
	add t0, t0, t3

	# flush the TLB because why not
	sfence.vma zero, zero
	# set satp to new value to enable paging
	csrw satp, t0
	# long jump to start filling TLB
	la t0, higher_half
	jr t0

# *** Paging functions below **
# lvl2_table_setup()
# inputs:
# s5 = 4K aligned starting physical address
# s6 = starting page table address
# s7 = pte attributes; 10 bits
# s8 = number of entries to map
# ra = return address; use JAL or JALR
lvl2_table_setup:
	# t0 = stating PPN
	li t0, PAGE_SIZE
	# PPN = phys_address / page_size
	divu t2, s5, t0
	xor t0, t0, t0
	add t0, t0, t2

	li t2, PAGES_PER_TABLE

	# t3 = global entry count
	xor t3, t3, t3

	# t4 = row index
	xor t4, t4, t4

	# t5 = level 2 table count
	xor t5, t5, t5
fill_lvl2_table:
	# check if we mapped enough entries
	blt t2, s8, continue_lvl2_fill
	jr ra
check_if_table_full:
	blt t4, t2, continue_lvl2_fill
move_to_next_lvl2_table:
	# TODO: check if we are out of bounds
	addi t5, t5, 0x1
	# reset the loop counters
	xor t4, t4, t4
	# s6 will already point to the next table
	# Note: this assumes contiguous storage!
continue_lvl2_fill:
	# clear pte
	xor t6, t6, t6

	# create pte
	# Upper half = PPN
	add t6, t6, t0
	slli t6, t6, 0xA
	# add lower half of PTE (attributes)
	add t6, t6, s7

	# mv pte to page slot
	sw t6, (s6)

	# prepare for next iteration
	# PPN++
	addi t0, t0, 0x1
	# row_index++
	addi t4, t4, 0x1
	# gloabl_entry_count++
	addi t3, t3, 0x1
	# page_table_offset += 4
	addi s6, s6, 0x4
	beq zero, zero, fill_lvl2_table


# lvl1_table_setup()
# inputs:
# s5 = starting physical address
# s6 = page directory start index
# s7 = pde attributes - 10 bits
# s8 = number of entries to map
# s9 = boolean: 0 for lvl2 mapping else 4mb mapping
# ra = return address; use JAL or JALR
lvl1_table_setup:
	# Note: we reuse t0 - t6
	# t0 = PPN of the target 4mb section
	xor t0, t0, t0
	xor t2, t2, t2
	li t0, PAGE_SIZE
	divu t2, s5, t0
	xor t0, t0, t0
	add t0, t0, t2

	# s0 = page directory offset
	# we need to point this to the "higher half offset"
	# first lets load the start address
	la s0, page_directory
	xor t1, t1, t1
	xor t2, t2, t2
	xor t3, t3, t3
	addi t2, t2, 0x4
	# pde offset = pde_index * 4
	mul t3, t2, s6
	# add offset to page directory pointer
	add s0, s0, t3

	# t4 = pde count
	xor t4, t4, t4
fill_lvl1_table:
	blt t4, s8, continue_lvl1_fill
	jr ra
continue_lvl1_fill:
	# t5 = current pde
	# first clear it
	xor t5, t5, t5
	# set ppn of current 4mb section
	add t5, t5, t0
	slli t5, t5, 0xA

	# set the lower half of pde
	beqz s9, clear_permission_bits
	add t5, t5, s7
	beqz zero, set_pde_entry
clear_permission_bits:
	li t6, 0xE
	xor t5, t5, t6
set_pde_entry:
	# move pde into page directory slot
	sw t5, (s0)

	# prepare for next iteration
	# pde_count++
	addi t4, t4, 0x1
	beqz s9, inc_page_ppn
	# 4mb ppn += 1024; point to next 4mb section
	addi t0, t0, 0x400
	beqz zero, next_pde
inc_page_ppn:
	# lvl2_page_table_ppn += 1; point to next table
	addi t0, t0, 0x1
next_pde:
	# page_directory_offset += 4
	addi s0, s0, 0x4

	beq zero, zero, fill_lvl1_table
.align 0x2
trap_boot_exceptions:
	csrr t0, mstatus
	csrr t1, mcause
	csrr t2, mbadaddr
	xor zero, zero, zero
	mret

# *** HIGHER HALF ****
.section .text
higher_half:
	# set up stack
	la sp, kernel_stack_bottom
	# call main
	call riscv_main
halt:
	j halt
	addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0
    addi zero, zero, 0

.align 0x4
.globl asm_machine_trap
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
	call riscv_handle_machine_interrupt
	# restore regs
	mret

.align 0x4
.globl asm_supervisor_trap
asm_supervisor_trap:
	call riscv_handle_supervisor_interrupt
	# TODO: eventually we should check xPP field to
	# return to the correct privilege level (USER | SUPERVISOR)
	sret
