/* Entry point */
ENTRY(boot_entry)

SECTIONS
{
        
    LOAD_ADDRESS = 0x80400000;
    
    . = LOAD_ADDRESS;
    BOOT_LOADER_TEXT_BEGIN = .;
    
    /* stage 1 boot code (boot loader) */
    .boot_text ALIGN(4K) : AT(LOAD_ADDRESS)
    {
		*(.boot_text)
	}
	BOOT_LOADER_TEXT_END = . - 1;
	
	BOOT_LOADER_BSS_BEGIN = .;
	/* stage 1 boot bss (boot loader) */
    .boot_bss ALIGN(4K) : AT(ADDR(.boot_bss))
    {
		*(.boot_bss)
	}
	BOOT_LOADER_BSS_END = .;
	/* Save the physaddr pointer */
	LMA_PTR = .;
	
    /* Set VMA to Virtual Base */
    . = KERNEL_VIRTUAL_BASE + (LMA_PTR - BOOT_LOADER_TEXT_BEGIN);
    
    KERNEL_TEXT_BEGIN = .;
    /* stage 2 */
    .text ALIGN(4K) : AT(LMA_PTR)
    {
		*(.text)
	}
	
	LMA_PTR = LMA_PTR + (. - KERNEL_VIRTUAL_BASE);
	KERNEL_TEXT_END = LMA_PTR - 1;
	
	KERNEL_RO_DATA_BEGIN = .;
	/* Read-only data. */
	.rodata ALIGN(4K) : AT(LMA_PTR)
	{
		*(.rodata)
	}
	
	LMA_PTR = LMA_PTR + (. - KERNEL_VIRTUAL_BASE);
	KERNEL_RO_DATA_END = LMA_PTR - 1;
	
	KERNEL_DATA_BEGIN = LMA_PTR;
	/* Read-write data (initialized) */
	.data ALIGN(4K) : AT(LMA_PTR)
	{
		*(.data)
	}
	
	LMA_PTR = LMA_PTR + (. - KERNEL_VIRTUAL_BASE);
	KERNEL_DATA_END = LMA_PTR - 1;
	
	KERNEL_BSS_BEGIN = LMA_PTR;
	/* Read-write data (uninitialized) and stack */
	.bss ALIGN(4K) :AT(LMA_PTR)
	{
		*(COMMON)
		*(.bss)
	}
	
	LMA_PTR = LMA_PTR + (. - KERNEL_VIRTUAL_BASE);
	KERNEL_BSS_END = LMA_PTR - 1;
    KERNEL_VIRTUAL_END = KERNEL_BSS_END;
    KERNEL_SIZE_IN_BYTES = KERNEL_BSS_END - BOOT_LOADER_TEXT_BEGIN;
}
