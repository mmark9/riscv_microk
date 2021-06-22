# build modes = normal/debug
BUILD_MODE?=debug
PREFIX=/opt/riscv/bin
TARGET_ARCH?=riscv32
HOST?=$(PREFIX)/$(TARGET_ARCH)-unknown-elf

# toolchain params
CC=$(HOST)-gcc
AS=$(HOST)-as
OBJCOPY=$(HOST)-objcopy

# Compile flags
ifeq ($(TARGET_ARCH),riscv64)
	ASFLAGS?=-mabi=lp64d
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

PROJECT_DIR=$(shell pwd)
DEST_DIR?=$(PROJECT_DIR)/release

# Misc.
VPATH=. asm/
LINKER_SCRIPT=linker.ld

# Output files
OPEN_SBI_PATH=opensbi
OPEN_SBI_BUILD_PATH=$(OPEN_SBI_PATH)/build/platform/generic/firmware
OPEN_SBI_PAYLOAD=$(DEST_DIR)/sal_os_$(TARGET_ARCH)_osbi_payload.elf
OPEN_SBI_JMP=$(DEST_DIR)/sal_os_$(TARGET_ARCH)_jmp.elf
KERNEL_IMAGE_ELF = $(DEST_DIR)/sal_os_$(TARGET_ARCH).elf
KERNEL_IMAGE_BINARY = $(DEST_DIR)/sal_os_$(TARGET_ARCH).bin

RV32_ASM_FILES=%/boot_loader.s %/context_low.s %/trap_low.s
RV64_ASM_FILES=%/boot_loader_rv64.s %/context_low_rv64.s %/trap_low_rv64.s

# Build objects
OBJS:=$(patsubst %.c,$(BUILD_DIR)/%.o, $(wildcard ./*.c))
ifeq ($(TARGET_ARCH),riscv64)
	ASM_OBJS:=$(patsubst %.s,%.s.o, $(filter-out $(RV32_ASM_FILES), $(wildcard asm/*.s)))
else
	ASM_OBJS:=$(patsubst %.s,%.s.o, $(filter-out $(RV64_ASM_FILES), $(wildcard asm/*.s)))
endif
ASM_OBJS:=$(notdir $(ASM_OBJS))
ASM_OBJS:=$(patsubst %.s.o, $(BUILD_DIR)/%.s.o, $(ASM_OBJS))


.PHONY: all $(MODULES)
# all1: $(KERNEL_IMAGE_ELF) $(KERNEL_IMAGE_BINARY) $(OPEN_SBI_PAYLOAD) $(OPEN_SBI_JMP)
all: $(KERNEL_IMAGE_ELF) $(OPEN_SBI_JMP)

$(KERNEL_IMAGE_ELF): $(OBJS) $(ASM_OBJS)
	$(CC) -T $(LINKER_SCRIPT) -o $@ $(CFLAGS) $(ASM_OBJS) $(OBJS) $(LIBFLAGS) -static-libgcc -lgcc

$(KERNEL_IMAGE_BINARY): $(KERNEL_IMAGE_ELF)
	$(OBJCOPY) -O binary $^ $@

$(OPEN_SBI_PAYLOAD): export CROSS_COMPILE = $(HOST)-
$(OPEN_SBI_PAYLOAD): $(KERNEL_IMAGE_BINARY)
	make -C $(OPEN_SBI_PATH) PLATFORM=generic FW_PAYLOAD=y FW_PAYLOAD_PATH=$<
	cp $(OPEN_SBI_BUILD_PATH)/fw_payload.elf $@

$(OPEN_SBI_JMP): export CROSS_COMPILE = $(HOST)-
$(OPEN_SBI_JMP): $(KERNEL_IMAGE_ELF)
	make -C $(OPEN_SBI_PATH) PLATFORM=generic FW_JUMP_ADDR=2155872256 FW_JUMP=y
	cp $(OPEN_SBI_BUILD_PATH)/fw_jump.elf $@

$(LINKER_SCRIPT): ;

clean:
	rm -f $(BUILD_DIR)/*
	rm -f $(KERNEL_IMAGE_ELF)
	rm -f $(KERNEL_IMAGE_BINARY)
	rm -f $(OPEN_SBI_PAYLOAD)
	rm -f $(OPEN_SBI_JMP)
	make -C $(OPEN_SBI_PATH) clean

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $^ -o $@ $(CFLAGS)

$(BUILD_DIR)/%.s.o: %.s
	mkdir -p $(BUILD_DIR)
	$(AS) $^ -o $@ $(ASFLAGS)

print-%:
	@echo $* = $($*)