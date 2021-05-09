# Constants for initial memory configuration
# This is a higher-half kernel that starts at 3.5GB mark
# TODO: maybe make this configureable somehow
.equ KERNEL_VIRTUAL_BASE, 0xE0000000
.equ VIRTUAL_MEMORY_SIZE, 0xFFFFFFFF
.equ FIRMWARE_LOAD_ADDRESS, 0x80000000
.equ KERNEL_LOAD_ADDRESS, 0x80800000
.globl KERNEL_VIRTUAL_BASE

# Constants set by the linker
.extern LOAD_ADDRESS
.extern KERNEL_TEXT_BEGIN
.extern KERNEL_TEXT_END
.extern KERNEL_RO_DATA_BEGIN
.extern KERNEL_RO_DATA_END
.extern KERNEL_DATA_BEGIN
.extern KERNEL_DATA_END
.extern KERNEL_BSS_BEGIN
.extern KERNEL_BSS_END
.extern KERNEL_TEXT_BEGIN_VIRTUAL
.extern KERNEL_TEXT_END_VIRTUAL
.extern KERNEL_RO_DATA_BEGIN_VIRTUAL
.extern KERNEL_RO_DATA_END_VIRTUAL
.extern KERNEL_DATA_BEGIN_VIRTUAL
.extern KERNEL_DATA_END_VIRTUAL
.extern KERNEL_BSS_BEGIN_VIRTUAL
.extern KERNEL_BSS_END_VIRTUAL
.extern KERNEL_VIRTUAL_END
.extern KERNEL_SIZE_IN_BYTES

# boot loader page table
# this should be replaced after getting
# to the kernel level boot code
.section .boot_bss, "aw", @nobits
.align 0xC
.global page_directory
page_directory:
    .skip 0x400 * 4, 0x0

# linker configuration
# helps the kernel map its pages with the correct
# attributes
.align 0x2
.section .rodata
linker_config:
    .long FIRMWARE_LOAD_ADDRESS
	.long LOAD_ADDRESS
	.long KERNEL_TEXT_BEGIN
	.long KERNEL_TEXT_END
	.long KERNEL_RO_DATA_BEGIN
	.long KERNEL_RO_DATA_END
	.long KERNEL_DATA_BEGIN
	.long KERNEL_DATA_END
	.long KERNEL_BSS_BEGIN
	.long KERNEL_BSS_END
	.long KERNEL_TEXT_BEGIN_VIRTUAL
    .long KERNEL_TEXT_END_VIRTUAL
    .long KERNEL_RO_DATA_BEGIN_VIRTUAL
    .long KERNEL_RO_DATA_END_VIRTUAL
    .long KERNEL_DATA_BEGIN_VIRTUAL
    .long KERNEL_DATA_END_VIRTUAL
    .long KERNEL_BSS_BEGIN_VIRTUAL
    .long KERNEL_BSS_END_VIRTUAL
	.long KERNEL_VIRTUAL_BASE
	.long KERNEL_VIRTUAL_END
	.long KERNEL_SIZE_IN_BYTES

# constants for table setup
.equ PAGE_SIZE, 0x1000
.equ PAGES_PER_TABLE, 0x400
.equ PAGE_TABLE_SIZE, PAGES_PER_TABLE * PAGE_SIZE
.equ KERNEL_PAGE_DIRECTORY_START_INDEX, KERNEL_VIRTUAL_BASE / 0x400000

.align 0x2
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
recursive_map:
    la s0, page_directory
    srli s0, s0, 12
    slli s0, s0, 10
    ori s1, s0, 7
    ori s2, s0, 1
    la s3, page_directory
    li s4, 4088
    add s3, s3, s4
    sw s1, 0(s3)
    addi s3, s3, 4
    sw s2, 0(s3)
boot_identity_map:
	# we start by creating
	# temp mappings
	# the kernel will create the real mappings later
	xor s5, s5, s5
	li a3, KERNEL_LOAD_ADDRESS
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
	# delegate all exceptions to supervisor
	# TODO makee this a conditional jump
	j supervisor_entry  # if opensbi is used
	li t0, 0xBBFF
	csrw medeleg, t0
	# delegate all interrupts to supervisor
	# (with the exception of Environment Call from M-mode)
	li t0, 0xBBF
	csrw mideleg, t0

	# first set machine trap vector
	# t0 = mtvec buffer; mode set to Direct implicitly
	# NOTE: base address should be aligned on 4 byte boundary!
	la t0, jump_to_supervisor

	# copy buffer to mtvec
	csrw mtvec, t0

	# ecalls are non-maskable since they are encoded
	# as illegal instructions; no need to enable interrupts
	# for this to work
	ecall
jump_to_supervisor:
	# reset trap vector for catching general errors with boot
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
jump_to_higher_half:
    # long jump to start filling TLB
    # a0 = boot hart id
    # a1 = device tree pointer or config string
    # a2 = config type: 0 = config string | 1 = device tree
    # a3 = linker config
    li a2, 0x1
    la a3, linker_config
    la t0, kernel_boot
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
# TODO: handle boot exceptions better
trap_boot_exceptions:
	csrr t0, mstatus
	csrr t1, mcause
	csrr t2, mbadaddr
	xor zero, zero, zero
	beqz zero, trap_boot_exceptions