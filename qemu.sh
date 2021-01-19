#!/bin/bash

if [ "$1" == "debug" ]; then
	echo "Debug On"
	qemu-system-riscv32 -machine virt -nographic -smp 1 -m 128M -bios release/sal_os_riscv32_osbi_payload.elf -s -S
else
	echo "Debug Off"
	qemu-system-riscv32 -machine virt -nographic -smp 1 -m 128M -bios release/sal_os_riscv32_osbi_payload.elf
fi
