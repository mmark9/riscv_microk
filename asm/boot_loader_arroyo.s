# Constants for initial memory configuration
# For RV64, kernel starts at 0x7fc0000000
# TODO: maybe make this configureable somehow
.equ KERNEL_VIRTUAL_BASE, 0xE0000000
.equ VIRTUAL_MEMORY_SIZE, 0x8000000000
.equ FIRMWARE_LOAD_ADDRESS, 0x80000000
.equ KERNEL_LOAD_ADDRESS, 0x80800000
.equ UART_TX_ADDR, 0x000C0020
.globl KERNEL_VIRTUAL_BASE

#strings
.section .boot_rodata, "a"
page_setup_str_str:
.string "kernel-boot: hit label page_setup_str\n"
paging_str_str:
.string "kernel-boot: hit label paging_str\n"
fw_stack_top_str:
.string "kernel-boot: hit label fw_stack_top\n"
fw_stack_bottom_str:
.string "kernel-boot: hit label fw_stack_bottom\n"
l2_table_str:
.string "kernel-boot: hit label l2_table\n"
l1_table_low_str:
.string "kernel-boot: hit label l1_table_low\n"
l1_table_high_str:
.string "kernel-boot: hit label l1_table_high\n"
l0_tables_low_str:
.string "kernel-boot: hit label l0_tables_low\n"
l0_tables_high_str:
.string "kernel-boot: hit label l0_tables_high\n"
linker_config_str:
.string "kernel-boot: hit label linker_config\n"
boot_entry_str:
.string "kernel-boot: hit label boot_entry\n"
setup_constants_str:
.string "kernel-boot: hit label setup_constants\n"
setup_exceptions_str:
.string "kernel-boot: hit label setup_exceptions\n"
recursive_map_lv2_str:
.string "kernel-boot: hit label recursive_map_lv2\n"
lv2_mapping_str:
.string "kernel-boot: hit label lv2_mapping\n"
lv2_identity_map_low_str:
.string "kernel-boot: hit label lv2_identity_map_low\n"
lv2_identity_map_high_str:
.string "kernel-boot: hit label lv2_identity_map_high\n"
lower_half_map_str:
.string "kernel-boot: hit label lower_half_map\n"
higher_half_map_str:
.string "kernel-boot: hit label higher_half_map\n"
level_0_map_low_str:
.string "kernel-boot: hit label level_0_map_low\n"
level_0_map_high_str:
.string "kernel-boot: hit label level_0_map_high\n"
lv1_link_lv0_tables_str:
.string "kernel-boot: hit label lv1_link_lv0_tables\n"
lv1_link_start_str:
.string "kernel-boot: hit label lv1_link_start\n"
lv1_link_continue_str:
.string "kernel-boot: hit label lv1_link_continue\n"
lv0_table_fill_str:
.string "kernel-boot: hit label lv0_table_fill\n"
lv0_table_fill_start_str:
.string "kernel-boot: hit label lv0_table_fill_start\n"
lv0_table_fill_continue_str:
.string "kernel-boot: hit label lv0_table_fill_continue\n"
enable_paging_str:
.string "kernel-boot: hit label enable_paging\n"
jump_to_higher_half_str:
.string "kernel-boot: hit label jump_to_higher_half\n"
kernel_marker:
.string "kernel-boot: test marker\n"

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

.section .bss_bss
.align 0x10
fw_stack_top:
.skip 0x4000
fw_stack_bottom:


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
.global l1_table_low
l1_table_low:
    .skip 0x200 * 8, 0x0

# this table is shared between
# both the intial identity map
# and the higher half mapping
.section .boot_bss, "aw", @nobits
.align 0xc
.global l1_table_high
l1_table_high:
    .skip 0x200 * 8, 0x0

# this table is shared between
# both the intial identity map
# and the higher half mapping
.section .boot_bss, "aw", @nobits
.align 0xc
.global l0_tables_low
l0_tables_low:
    .skip 0x200 * 8 * 8, 0x0

# this table is shared between
# both the intial identity map
# and the higher half mapping
.section .boot_bss, "aw", @nobits
.align 0xc
.global l0_tables_high
l0_tables_high:
    .skip 0x200 * 8 * 16, 0x0


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
	la a4, boot_entry_str
	jal a7,early_puts
setup_constants:
    la a4,setup_constants_str
    jal a7,early_puts
    # tp = 2MiB in PPN
    li tp,0x200
    # gp = 1GiB
    li gp,0x1
    slli gp,gp,0x1e
setup_exceptions:
    la a4,setup_exceptions_str
    jal a7,early_puts

    la t0, trap_boot_exceptions
    csrw stvec, t0
recursive_map_lv2:
    # to enable editing page tables
    # after sditching satp MODE to sv39
    # we use recursive mapping entries
    la a4,recursive_map_lv2_str
    jal a7,early_puts

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
    la a4,lv2_mapping_str
    jal a7,early_puts

    la s0,l2_table
lv2_identity_map_low:
    la a4,lv2_identity_map_low
    jal a7,early_puts
    # setup PTE to point to l1 table
    la s6,l1_table_low
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
    #li s2,0x8
    # s5 points to page table slot
    slli s4,s1,3
    #mul s4,s1,s2
    add s5,s0,s4
    # set the entry for the identity mapping
    sd t0,0(s5)
lv2_identity_map_high:
    la a4,lv2_identity_map_high_str
    jal a7,early_puts

    la s6,l1_table_high
    srli s6,s6,0xc
    # s6 = PPN of l1_table
    slli t0,s6,0xa
    # t0 = PTE with only PPN
    # set valid bit only since this is a pointer
    addi t0,t0,0x1
    # t0 = PTE
    xor s5,s5,s5
    # we only need to two mappings
    li s1,IMAGE_HIGHER_HALF_PAGE_TABLE_START_INDEX
    #li s2,0x8
     # s5 points to page table slot
    slli s4,s1,3
    #mul s4,s1,s2
    add s5,s0,s4
    # s5 now points to higher half table slot
    sd t0,0(s5)
lower_half_map:
    la a4,lower_half_map_str
    jal a7,early_puts

    la s0,l0_tables_low
    li s1,0x8
    li a3,FIRMWARE_LOAD_ADDRESS
    la s5,l1_table_low
    jal lv1_link_lv0_tables
higher_half_map:
    la a4,higher_half_map
    jal a7,early_puts

    la s0,l0_tables_high
    li s1,0x80
    li a3,KERNEL_VIRTUAL_BASE
    la s5,l1_table_high
    jal lv1_link_lv0_tables
   # s0 = l0_tables_pointer
   # s1 = how many level0 entries
   # a3 = physical address pointer
level_0_map_low:
    la a4,level_0_map_low_str
    jal a7,early_puts

    la s0,l0_tables_low
    li t0,512
    li t1,0x8
    # s1 = 16 (tables) * 512
    slli s1,t0,3
    #mul s1,t1,t0
    li a3,FIRMWARE_LOAD_ADDRESS
    # s1 = # pages * 512
    jal lv0_table_fill
level_0_map_high:
    la a4,level_0_map_high_str
    jal a7,early_puts

    la s0,l0_tables_high
    li t0,512
    li t1,0x10
    # s1 = 16 (tables) * 512
    slli s1,t0,3
    #mul s1,t1,t0
    li a3,KERNEL_LOAD_ADDRESS
    # s1 = # pages * 512
    jal lv0_table_fill
    j enable_paging
lv1_link_lv0_tables:
    la a4,lv1_link_lv0_tables_str
    jal a7,early_puts

    # inputs:
    # s0 = level 0 table pointer
    # s1 = number of level 0 mappings = number of 2 MiB regions
    # s5 = level 1 table pointer
    # a3 = physical pointer
    # temps:
    # s2 = lv1 table index
    # s3 = lv0 table_index
    # s4 = table offset
    # s6 = PTE

	#la s0, l0_tables
	#li s1, 0x10

	# determine index in level 1 table
	#li a3,FIRMWARE_LOAD_ADDRESS
	# t0 = 511
	# capture lv1 index in s2
	li t0,0x1ff
	slli t0,t0,0x15
	and t0,t0,a3
	srli t0,t0,0x15
	mv s2,t0

	#la s5, l1_table
	#li t0,0x8
	slli s2,s2,3
	#mul s2,s2,t0
	# s2 = offset (8 * level 1 index)
	add s5,s5,s2

	xor s3,s3,s3
	li s4, 0x1000

lv1_link_start:
    la a4,lv1_link_start_str
    jal a7,early_puts

    blt s3,s1,lv1_link_continue
    # jump back
    jr ra
lv1_link_continue:
    la a4,lv1_link_continue
    jal a7,early_puts

    mv s6,s0
    # divide by PAGE_SIZE = 4096
    srli s6,s6,0xc
    slli s6,s6,0xa
    # set valid bit
    addi s6,s6,0x1
    # s6 = PTE
    sd s6,0(s5)
    # increment level 0 table pointer
    add s0,s0,s4
    # move to next level 1 table slot
    addi s5,s5,0x8
    addi s3,s3,0x1
    j lv1_link_start
lv0_table_fill:
    la a4,lv0_table_fill_str
    jal a7,early_puts

    # inputs:
    # s0 = l0_tables_pointer
    # s1 = how many level0 entries
    # a3 = physical address pointer

    # temps:
    # s2 = level 0 index
    # s4 = FRAME size
    # s5 = PTE
    #la s0, l0_tables
    li s4, 0x1000

    # determine index in level 1 table
    #li a3,FIRMWARE_LOAD_ADDRESS

    li t0,0x1ff
    slli t0,t0,0xc
    and t0,t0,a3
    srli t0,t0,0xc
    mv s2,t0
    # s2 should be zero
lv0_table_fill_start:
    #la a4,lv0_table_fill_start_str
    #jal a7, early_puts

    blt s2,s1,lv0_table_fill_continue
    jr ra
lv0_table_fill_continue:
    #la a4,lv0_table_fill_continue_str
    #jal a7,early_puts

    mv s5,a3
    # divide by PAGE_SIZE = 4096
    srli s5,s5,0xc
    slli s5,s5,0xa
    # set RWXV
    addi s5,s5,0xf
    # save in level 0 table
    sw s5,0(s0)
    # increment table pointer
    addi s0,s0,0x8
    # increment physical pointer
    add a3,a3,s4
    addi s2,s2,0x1
    j lv0_table_fill_start
enable_paging:
    la a4,enable_paging_str
    jal a7,early_puts

	# t0 = used to copy to satp reg
	xor t0, t0, t0
	# Set mode = 8 (sv39) and ASID = 0
	addi t0, t0, 0x8
	slli t0, t0, 0x3c

	# set PPN of page directory (lvl1 table)
	xor t1, t1, t1
	xor t2, t2, t2
	xor t3, t3, t3
	# li t1, PAGE_SIZE
	la t2, l2_table
	# t3 = ppn(page_directory)
	srli t3,t2,0xc
	#divu t3, t2, t1

	# set PPN in satp buffer (t3)
	add t0, t0, t3

	la a4,kernel_marker
    jal a7,early_puts
	# flush the TLB because why not
	sfence.vma zero, zero
	# set satp to new value to enable paging
	la a4,kernel_marker
    jal a7,early_puts
	csrw satp, t0
	#la a4,kernel_marker
    #jal a7,early_puts
jump_to_higher_half:
    #la a4,jump_to_higher_half_str
    #jal a7,early_puts
    # long jump to start filling TLB
    # a0 = boot hart id
    # a1 = device tree pointer or config string
    # a2 = config type: 0 = config string | 1 = device tree
    # a3 = linker config
    li a2, 0x1
    la a3, linker_config
    la t0, kernel_boot
	jr t0

early_puts:
    # a4 = string
    # a5 = character
    # a6 = UART TX ADDR
    # a7 = holds return address
    li a6,UART_TX_ADDR
early_puts_cont:
    lb a5,0(a4)
    bnez a5,early_putc
    jr a7
early_putc:
    sb a5,0(a6)
    addi a4,a4,0x1
    beqz zero,early_puts_cont

.align 0x2
# TODO: handle boot exceptions better
trap_boot_exceptions:
	csrr t0, sstatus
	csrr t1, scause
	csrr t2, sbadaddr
	xor zero, zero, zero
	beqz zero, trap_boot_exceptions