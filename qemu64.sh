#!/bin/bash

if [ "$1" == "debug" ]; then
	echo "Debug On"
	qemu-system-riscv64 -machine virt -nographic -smp 1 -m 128M -bios release/sal_os_riscv64_jmp.elf -kernel release/sal_os_riscv64.elf -s -S
else
	echo "Debug Off"
	qemu-system-riscv64 -machine virt -nographic -smp 1 -m 128M -bios release/sal_os_riscv64_jmp.elf -kernel release/sal_os_riscv64.elf
fi
