# Constants for initial memory configuration
# For RV64, kernel starts at 0x7fc0000000
# TODO: maybe make this configureable somehow
.equ KERNEL_VIRTUAL_BASE, 0xE0000000
.equ VIRTUAL_MEMORY_SIZE, 0x8000000000
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
.align 0xc
.global l2_table
l2_table:
    .skip 0x200 * 8, 0x0

# this table is shared between
# both the intial identity map
# and the higher half mapping
.section .boot_bss, "aw", @nobits
.align 0xc
.global l1_table_hh
l1_table_hh:
    .skip 0x200 * 8, 0x0

# this table is shared between
# both the intial identity map
# and the higher half mapping
.section .boot_bss, "aw", @nobits
.align 0xc
.global l1_table_fw
l1_table_fw:
    .skip 0x200 * 8, 0x0


# linker configuration
# helps the kernel map its pages with the correct
# attributes
.align 0x2
.section .rodata
linker_config:
    .dword FIRMWARE_LOAD_ADDRESS
	.dword LOAD_ADDRESS
	.dword KERNEL_TEXT_BEGIN
	.dword KERNEL_TEXT_END
	.dword KERNEL_RO_DATA_BEGIN
	.dword KERNEL_RO_DATA_END
	.dword KERNEL_DATA_BEGIN
	.dword KERNEL_DATA_END
	.dword KERNEL_BSS_BEGIN
	.dword KERNEL_BSS_END
	.dword KERNEL_TEXT_BEGIN_VIRTUAL
    .dword KERNEL_TEXT_END_VIRTUAL
    .dword KERNEL_RO_DATA_BEGIN_VIRTUAL
    .dword KERNEL_RO_DATA_END_VIRTUAL
    .dword KERNEL_DATA_BEGIN_VIRTUAL
    .dword KERNEL_DATA_END_VIRTUAL
    .dword KERNEL_BSS_BEGIN_VIRTUAL
    .dword KERNEL_BSS_END_VIRTUAL
	.dword KERNEL_VIRTUAL_BASE
	.dword KERNEL_VIRTUAL_END
	.dword KERNEL_SIZE_IN_BYTES

# constants for table setup
.equ PAGE_SIZE, 0x1000
.equ PAGES_PER_TABLE, 0x200
.equ PAGE_TABLE_SIZE, PAGES_PER_TABLE * PAGE_SIZE
.equ IMAGE_HIGHER_HALF_PAGE_TABLE_START_INDEX, KERNEL_VIRTUAL_BASE / 0x40000000
.equ IMAGE_IDENTITY_PAGE_TABLE_START_INDEX, FIRMWARE_LOAD_ADDRESS / 0x40000000

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
setup_constants:
    # tp = 2MiB in PPN
    li tp,0x200
    # gp = 1GiB
    li gp,0x1
    slli gp,gp,0x1e
setup_exceptions:
    la t0, trap_boot_exceptions
    csrw stvec, t0
recursive_map_lv2:
    # to enable editing page tables
    # after sditching satp MODE to sv39
    # we use recursive mapping entries
    la s0,l2_table
    srli s0,s0,12
    slli s0,s0,10
    ori s1,s0,7
    ori s2,s0,1
    la s3,l2_table
    # point to recursive entries
    li s4,4080
    add s3,s3,s4
    # store recursive maps
    sd s1,0(s3)
    sd s2,8(s3)
lv2_mapping:
    # now set pte entries in lv2 table
    la s0,l2_table
lv2_identity_map:
    # setup PTE to point to l1 table
    la s6,l1_table_fw
    srli s6,s6,0xc
    # s6 = PPN of l1_table
    slli t0,s6,0xa
    # t0 = PTE with only PPN
    # set valid bit only since this is a pointer
    addi t0,t0,0x1
    # t0 = PTE
    xor s5,s5,s5
    # we only need to two mappings
    li s1,IMAGE_IDENTITY_PAGE_TABLE_START_INDEX
    li s2,0x8
    # s5 points to page table slot
    mul s4,s1,s2
    add s5,s0,s4
    # set the entry for the identity mapping
    sd t0,0(s5)
    # now setup the higher half mapping
lv2_higher_half_map:
    # setup PTE to point to l1 table
    la s6,l1_table_hh
    srli s6,s6,0xc
    # s6 = PPN of l1_table
    slli t0,s6,0xa
    # t0 = PTE with only PPN
    # set valid bit only since this is a pointer
    addi t0,t0,0x1
    # t0 = PTE
    li s1,IMAGE_HIGHER_HALF_PAGE_TABLE_START_INDEX
    li s2,0x8
    mul s4,s1,s2
    add s5,s0,s4
    # s5 now points to higher half table slot
    sd t0,0(s5)
boot_identity_map_lv1:
	# map the kernel/firmware to a level 1 (second-level)
	# this is temp mapping which should be enough to get us
	# into C-land with paging enabled.
	li a3,FIRMWARE_LOAD_ADDRESS
	mv s5,a3
	# t0 = 511
	# capture lv1 index in s6
	li t0,0x1ff
	slli t0,t0,0x15
	and t0,t0,a3
	srli t0,t0,0x15
	mv s6,t0

	li s7, 0xF
	# 8 * 2MiB = 16 MiB
	li s8, 0x8
	la s9,l1_table_fw
	jal lvl1_table_setup
higher_half_map_lv1:
	# map the kernel/firmware to a level 1 (second-level)
	# higher half of the address space.
	li s5,KERNEL_LOAD_ADDRESS
	li a3, KERNEL_VIRTUAL_BASE
	# t0 = 511
	# capture lv1 index in s6
	li t0,0x1ff
	slli t0,t0,0x15
	and t0,t0,a3
	srli t0,t0,0x15
	mv s6,t0

	li s7, 0xF
	# 8 * 2MiB = 32 MiB
	li s8, 0x10
	la s9,l1_table_hh
	jal lvl1_table_setup
map_device_tree:
    li s5,0x87000000
	li a3, 0x87000000
	# t0 = 511
	# capture lv1 index in s6
	li t0,0x1ff
	slli t0,t0,0x15
	and t0,t0,a3
	srli t0,t0,0x15
	mv s6,t0

	li s7, 0xF
	# 1 * 2MiB
	li s8, 0x1
	la s9,l1_table_fw
	jal lvl1_table_setup
enable_paging:
	# t0 = used to copy to satp reg
	xor t0, t0, t0
	# Set mode = 8 (sv39) and ASID = 0
	addi t0, t0, 0x8
	slli t0, t0, 0x3c

	# set PPN of page directory (lvl1 table)
	xor t1, t1, t1
	xor t2, t2, t2
	xor t3, t3, t3
	li t1, PAGE_SIZE
	la t2, l2_table
	# t3 = ppn(page_directory)
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

# lvl1_table_setup()
# inputs:
# s5 = starting physical address
# s6 = page directory start index
# s7 = pte attributes - 10 bits
# s8 = number of entries to map
# s9 = pointer to page table
# ra = return address; use JAL or JALR

# L1 table is the second level table
# that will serve as the leaf of the
# translation tree and hence we use 2MiB pages
lvl1_table_setup:
	# Note: we reuse t0 - t6
	# t0 = PPN of the target 2MiB section
	xor t0, t0, t0
	xor t2, t2, t2
	li t0, PAGE_SIZE
	# t2 = s5 / t0 (PAGE_SIZE)
	divu t2, s5, t0
	xor t0, t0, t0
	add t0, t0, t2

	# s0 = pointer to level 1 page table
	mv s0,s9
	xor t1, t1, t1
	xor t2, t2, t2
	xor t3, t3, t3
	addi t2, t2, 0x8
	# t3 = offset within the l1 table
	# pte_offset = pte_index (s6) * 8
	mul t3, t2, s6
	# add offset to page table pointer
	# s0 now points to the address of the page table slot
	add s0, s0, t3

	# t4 = pte counter
	xor t4, t4, t4
fill_lvl1_table:
	blt t4, s8, continue_lvl1_fill
	jr ra
continue_lvl1_fill:
	# t5 = current pte
	# first clear it
	xor t5, t5, t5
	# set ppn of current 4KiB section
	add t5, t5, t0
	slli t5, t5, 0xa
	# t5 now has the PPN set but no permissions
	# or other attributes

	# set the lower half of pte
	#beqz s9, clear_permission_bits
	# set permissions defined in s7
	add t5, t5, s7
	beqz zero, set_pte_entry
clear_permission_bits:
	li t6, 0xE
	xor t5, t5, t6
set_pte_entry:
	# move pte into page directory slot
	sd t5, 0(s0)

	# prepare for next iteration
	# pte_count++
	addi t4, t4, 0x1
	#beqz s9, inc_page_ppn
	# set t0 the next PPN in the sequence
	add t0,t0,tp
	beqz zero, next_pte
inc_page_ppn:
	# lvl2_page_table_ppn += 1; point to next table
	addi t0, t0, 0x1
next_pte:
	# point page_table pointer to next slot
	addi s0, s0, 0x8
	# continue the loop
	beqz zero, fill_lvl1_table

.align 0x2
# TODO: handle boot exceptions better
trap_boot_exceptions:
	csrr t0, sstatus
	csrr t1, scause
	csrr t2, sbadaddr
	xor zero, zero, zero
	beqz zero, trap_boot_exceptions