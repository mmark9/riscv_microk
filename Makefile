# build modes = normal/debug
BUILD_MODE?=debug
#PREFIX=/opt/riscv_vanilla/bin
PREFIX=/opt/riscv/bin
TARGET_ARCH?=riscv32
HOST?=$(PREFIX)/$(TARGET_ARCH)-unknown-elf

LOAD_ADDRESS?=0x80000000

ifeq ($(TARGET_ARCH),riscv64)
	ISA=rv64imafdc
	ARCH_WIDTH=64
else
	ISA=rv32ia
	ARCH_WIDTH=32
endif

# toolchain params
CC=$(HOST)-gcc
AS=$(HOST)-as
OBJCOPY=$(HOST)-objcopy
OBJDUMP=$(HOST)-objdump

FW_JUMP_ADDR?=2155872256
SBI_PLATFORM?=generic

# Compile flags
ifeq ($(TARGET_ARCH),riscv64)
	ASFLAGS?=-mabi=lp64
else
	ASFLAGS?=-mabi=ilp32
endif
CFLAGS:=-O0 -std=gnu99 \
	-ffreestanding -fbuiltin -Wall -Wextra -I ./
ifeq ($(BUILD_MODE),debug)
	CFLAGS:=$(CFLAGS) -gdwarf-4
endif
ifeq ($(TARGET_ARCH),riscv64)
	CFLAGS:=$(CFLAGS) -fPIC
endif
LIBFLAGS:=-nostdlib

# Directories
ifeq ($(BUILD_MODE),debug)
	BUILD_DIR:=$(shell pwd)/build/debug
else
	BUILD_DIR:=$(shell pwd)/build/normal
endif

QEMU?=y
ifeq ($(QEMU),y)
	CCFLAGS:=$(CCFLAGS) -D QEMU
endif

PROJECT_DIR=$(shell pwd)
DEST_DIR?=$(PROJECT_DIR)/release

# Misc.
VPATH=. asm/
LINKER_SCRIPT=linker.ld
ARROYO_LINKER_SCRIPT=arroyo_linker.ld
ARROYO_FPGA_LINKER_SCRIPT=arroyo_linker_fpga.ld

ARROYO_FPGA_FW_PAD_SIZE=16384
KERNEL_FPGA_BINARY_PAD_SIZE=204800
FPGA_IMAGE_PAD_SIZE=261376

# Output files
OPEN_SBI_PATH=opensbi
OPEN_SBI_BUILD_PATH=$(OPEN_SBI_PATH)/build/platform/$(SBI_PLATFORM)/firmware
OPEN_SBI_PAYLOAD_ELF=$(DEST_DIR)/sal_os_$(TARGET_ARCH)_osbi_payload.elf
OPEN_SBI_PAYLOAD_BINARY=$(DEST_DIR)/sal_os_$(TARGET_ARCH)_osbi_payload.bin
OPEN_SBI_JMP_ELF=$(DEST_DIR)/sal_os_$(TARGET_ARCH)_jmp.elf
OPEN_SBI_JMP_BINARY=$(DEST_DIR)/sal_os_$(TARGET_ARCH)_jmp.bin
KERNEL_IMAGE_ELF=$(DEST_DIR)/sal_os_$(TARGET_ARCH).elf
KERNEL_IMAGE_BINARY=$(DEST_DIR)/sal_os_$(TARGET_ARCH).bin
KERNEL_FPGA_IMAGE_BINARY=$(DEST_DIR)/sal_os_$(TARGET_ARCH)_fgpa.bin
FPGA_KERNEL_MEMORY_IMAGE=$(DEST_DIR)/kernel.vmh
ARROYO_FW_IMAGE=$(DEST_DIR)/arroyo_fw.elf
ARROYO_FPGA_FW_IMAGE=$(DEST_DIR)/arroyo_fw_fpga.elf
ARROYO_FW_BINARY=$(DEST_DIR)/arroyo_fw.bin
ARROYO_FPGA_FW_BINARY=$(DEST_DIR)/arroyo_fw_fpga.bin
ARROYO_FW_MEMORY_IMAGE=$(DEST_DIR)/arroyo_fw.vmh
RV32_ASM_FILES=%/boot_loader.s %/context_low.s %/trap_low.s
RV64_ASM_FILES=%/boot_loader_arroyo.s %/context_low_rv64.s %/trap_low_rv64.s
ARROYO_FW_ASM_FILES=asm/fw_entry.s
ARROYO_FW_C_FILES=./fw_main.c
FPGA_SIM_MEMORY_IMAGE=$(DEST_DIR)/arroyo_fw_os.vmh
FPGA_BINARY_IMAGE=$(DEST_DIR)/arroyo_fw_os.bin

# Build objects
KERNEL_CXX_OBJS:=$(patsubst %.c,$(BUILD_DIR)/%.o, \
	$(filter-out $(ARROYO_FW_C_FILES), $(wildcard ./*.c)))
ifeq ($(TARGET_ARCH),riscv64)
	KERNEL_ASM_OBJS:=$(patsubst %.s,%.s.o, \
		$(filter-out $(RV32_ASM_FILES) $(ARROYO_FW_ASM_FILES), $(wildcard asm/*.s)))
else
	KERNEL_ASM_OBJS:=$(patsubst %.s,%.s.o, \
		$(filter-out $(RV64_ASM_FILES) $(ARROYO_FW_ASM_FILES), $(wildcard asm/*.s)))
endif
KERNEL_ASM_OBJS:=$(notdir $(KERNEL_ASM_OBJS))
KERNEL_ASM_OBJS:=$(patsubst %.s.o, $(BUILD_DIR)/%.s.o, $(KERNEL_ASM_OBJS))

ARROYO_FW_OBJS:=$(BUILD_DIR)/fw_entry.s.o $(BUILD_DIR)/fw_main.o

.PHONY: sim fpga fpga_sim
sim: $(KERNEL_IMAGE_ELF) $(OPEN_SBI_JMP_ELF)
fpga: $(FPGA_BINARY_IMAGE)
fpga_sim: $(FPGA_SIM_MEMORY_IMAGE)

$(FPGA_BINARY_IMAGE): $(ARROYO_FPGA_FW_BINARY) $(KERNEL_FPGA_IMAGE_BINARY)
	cat $^ > $@
	./pad_binary.py $@ $(FPGA_IMAGE_PAD_SIZE)

$(FPGA_SIM_MEMORY_IMAGE): $(ARROYO_FW_MEMORY_IMAGE) $(FPGA_KERNEL_MEMORY_IMAGE)
	cat $^ > $@

$(ARROYO_FW_MEMORY_IMAGE): $(ARROYO_FW_IMAGE)
	./gen_vmh $^ $@ 32 $(LOAD_ADDRESS)

$(ARROYO_FW_IMAGE): $(ARROYO_FW_OBJS)
	$(CC) -T $(ARROYO_LINKER_SCRIPT) -o $@ $(CFLAGS) $^ $(LIBFLAGS) -static-libgcc -lgcc

$(ARROYO_FPGA_FW_IMAGE): $(ARROYO_FW_OBJS)
	$(CC) -T $(ARROYO_FPGA_LINKER_SCRIPT) -o $@ $(CFLAGS) $^ $(LIBFLAGS) -static-libgcc -lgcc

$(FPGA_KERNEL_MEMORY_IMAGE): $(KERNEL_IMAGE_ELF)
	./gen_vmh $^ $@ 32 $(LOAD_ADDRESS)

$(KERNEL_IMAGE_ELF): $(KERNEL_CXX_OBJS) $(KERNEL_ASM_OBJS)
	$(CC) -T $(LINKER_SCRIPT) -o $@ $(CFLAGS) $(KERNEL_ASM_OBJS) $(KERNEL_CXX_OBJS) $(LIBFLAGS) -static-libgcc -lgcc

$(ARROYO_FW_BINARY): $(ARROYO_FW_IMAGE)
	$(OBJCOPY) -O binary $^ $@

$(ARROYO_FPGA_FW_BINARY): $(ARROYO_FPGA_FW_IMAGE)
	$(OBJCOPY) -O binary $^ $@
	./pad_binary.py $@ $(ARROYO_FPGA_FW_PAD_SIZE)

$(KERNEL_FPGA_IMAGE_BINARY): $(KERNEL_IMAGE_BINARY)
	cp $^ $@
	./pad_binary.py $@ $(KERNEL_FPGA_BINARY_PAD_SIZE)

$(KERNEL_IMAGE_BINARY): $(KERNEL_IMAGE_ELF)
	$(OBJCOPY) -O binary $^ $@ --set-section-flags .boot_bss=alloc,load,contents

$(OPEN_SBI_PAYLOAD_ELF): export CROSS_COMPILE = $(HOST)-
$(OPEN_SBI_PAYLOAD_ELF): $(KERNEL_IMAGE_BINARY)
	make -C $(OPEN_SBI_PATH) PLATFORM=$(SBI_PLATFORM) FW_PAYLOAD=y FW_PAYLOAD_PATH=$< PLATFORM_RISCV_ISA=$(ISA)
	cp $(OPEN_SBI_BUILD_PATH)/fw_payload.elf $@

$(OPEN_SBI_PAYLOAD_BINARY): export CROSS_COMPILE = $(HOST)-
$(OPEN_SBI_PAYLOAD_BINARY): $(KERNEL_IMAGE_BINARY)
	make -C $(OPEN_SBI_PATH) PLATFORM=$(SBI_PLATFORM) FW_PAYLOAD=y FW_PAYLOAD_PATH=$< PLATFORM_RISCV_ISA=$(ISA)
	cp $(OPEN_SBI_BUILD_PATH)/fw_payload.bin $@

$(OPEN_SBI_JMP_ELF): export CROSS_COMPILE = $(HOST)-
$(OPEN_SBI_JMP_ELF): $(KERNEL_IMAGE_ELF)
	make -C $(OPEN_SBI_PATH) PLATFORM=$(SBI_PLATFORM) FW_JUMP_ADDR=$(FW_JUMP_ADDR) FW_JUMP=y
	cp $(OPEN_SBI_BUILD_PATH)/fw_jump.elf $@

$(OPEN_SBI_JMP_BINARY): export CROSS_COMPILE = $(HOST)-
$(OPEN_SBI_JMP_BINARY): $(KERNEL_IMAGE_ELF)
	make -C $(OPEN_SBI_PATH) PLATFORM=$(SBI_PLATFORM) FW_JUMP_ADDR=$(FW_JUMP_ADDR) FW_JUMP=y PLATFORM_RISCV_ISA=$(ISA)
	cp $(OPEN_SBI_BUILD_PATH)/fw_jump.bin $@

$(LINKER_SCRIPT): ;

clean:
	rm -f $(BUILD_DIR)/*
	rm -f $(DEST_DIR)/*
	make -C $(OPEN_SBI_PATH) clean

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $^ -o $@ $(CFLAGS)

$(BUILD_DIR)/%.s.o: %.s
	mkdir -p $(BUILD_DIR)
	$(AS) $^ -o $@ $(ASFLAGS)

print-%:
	@echo $* = $($*)