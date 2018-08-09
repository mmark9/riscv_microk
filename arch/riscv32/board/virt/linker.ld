/* Entry point */
ENTRY(boot_entry)

SECTIONS
{
        /* 
        The following constants are defined in boot.S.
        This setup is ideally for a higher half kernel setup.
        KERNEL_LOAD_ADDRESS --> Where the kernel should be loaded in memory
        KERNEL_VIRTUAL_BASE  --> Where the kernel should think it is in memory when paging is on
        */
        
	LOAD_ADDRESS = 0x80000000;
    
    . = LOAD_ADDRESS;
  
    /* stage 1 boot code */
    .boot_text ALIGN(4K) : AT(LOAD_ADDRESS)
    {
		*(.boot_text)
	}
	
	/* stage 1 boot data */
	.boot_data ALIGN(4K) : AT(ADDR(.boot_data))
	{
	    *(.boot_data)
	}
	
	/* stage 1 boot bss */
	.boot_bss ALIGN(4K) : AT(ADDR(.boot_bss))
	{
	    *(.boot_bss)
	}
	
	/* Save the physaddr pointer */
	LMA_PTR = .; 
	
    /* Set VMA to Virtual Base */
    . = KERNEL_VIRTUAL_BASE;
    
    /* stage 2 */
    .text ALIGN(4K) : AT(LMA_PTR)
    {
		*(.text)
	}
	
	LMA_PTR = LMA_PTR + (. - KERNEL_VIRTUAL_BASE);
	
	/* Read-only data. */
	.rodata ALIGN(4K) : AT(LMA_PTR)
	{
		*(.rodata)
	}
	
	LMA_PTR = LMA_PTR + (. - KERNEL_VIRTUAL_BASE);
	
	/* Read-write data (initialized) */
	.data ALIGN(4K) : AT(LMA_PTR)
	{
		*(.data)
	}
	
	LMA_PTR = LMA_PTR + (. - KERNEL_VIRTUAL_BASE);
	
	/* Read-write data (uninitialized) and stack */
	.bss ALIGN(4K) :AT(LMA_PTR)
	{
		*(COMMON)
		*(.bss)
	}
    KERNEL_VIRTUAL_END = .;
    KERNEL_SIZE_IN_BYTES = KERNEL_VIRTUAL_END - KERNEL_VIRTUAL_BASE;
}
