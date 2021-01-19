#!/bin/bash

if [ "$1" == "debug" ]; then
	echo "Debug On"
	qemu-system-riscv32 -machine virt -nographic -smp 1 -m 128M -bios default -kernel release/sal_os_riscv32.elf -s -S
else
	echo "Debug Off"
	qemu-system-riscv32 -machine virt -nographic -smp 1 -m 128M -bios default -kernel release/sal_os_riscv32.elf
fi
