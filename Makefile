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
ASFLAGS?=-mabi=ilp32
CFLAGS:=-O0 -std=gnu99 \
	-ffreestanding -fbuiltin -Wall -Wextra -I ./
ifeq ($(BUILD_MODE),debug)
	CFLAGS:=$(CFLAGS) -gdwarf-4
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
KERNEL_IMAGE_ELF = $(DEST_DIR)/sal_os_$(TARGET_ARCH).elf
KERNEL_IMAGE_BINARY = $(DEST_DIR)/sal_os_$(TARGET_ARCH).bin

# Build objects
OBJS:=$(patsubst %.c,$(BUILD_DIR)/%.o, $(wildcard ./*.c))
ASM_OBJS:=$(patsubst %.s,%.s.o, $(wildcard asm/*.s))
ASM_OBJS:=$(notdir $(ASM_OBJS))
ASM_OBJS:=$(patsubst %.s.o, $(BUILD_DIR)/%.s.o, $(ASM_OBJS))


.PHONY: all $(MODULES)

all: $(KERNEL_IMAGE_ELF) $(KERNEL_IMAGE_BINARY) $(OPEN_SBI_PAYLOAD)

$(KERNEL_IMAGE_ELF): $(OBJS) $(ASM_OBJS)
	$(CC) -T $(LINKER_SCRIPT) -o $@ $(CFLAGS) $(ASM_OBJS) $(OBJS) $(LIBFLAGS) -static-libgcc -lgcc

$(KERNEL_IMAGE_BINARY): $(KERNEL_IMAGE_ELF)
	$(OBJCOPY) -O binary $^ $@

$(OPEN_SBI_PAYLOAD): export CROSS_COMPILE = $(HOST)-
$(OPEN_SBI_PAYLOAD): $(KERNEL_IMAGE_BINARY)
	make -C $(OPEN_SBI_PATH) PLATFORM=generic FW_PAYLOAD=y FW_PAYLOAD_PATH=$<
	cp $(OPEN_SBI_BUILD_PATH)/fw_payload.elf $@


$(LINKER_SCRIPT): ;

clean:
	rm -f $(BUILD_DIR)/*
	rm -f $(KERNEL_IMAGE_ELF)
	rm -f $(KERNEL_IMAGE_BINARY)
	rm -f $(OPEN_SBI_PAYLOAD)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $^ -o $@ $(CFLAGS)

$(BUILD_DIR)/%.s.o: %.s
	mkdir -p $(BUILD_DIR)
	$(AS) $^ -o $@ $(ASFLAGS)

print-%:
	@echo $* = $($*)