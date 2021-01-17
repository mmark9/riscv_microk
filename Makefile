# build modes = normal/debug
BUILD_MODE?=debug

# Compile flags
# TODO: make this configurable
ASFLAGS?=-mabi=ilp32
CFLAGS:=-O0 -std=gnu99 \
	-ffreestanding -fbuiltin -Wall -Wextra
ifeq ($(BUILD_MODE),debug)
CFLAGS:=$(CFLAGS) -gdwarf-4
endif
LIBFLAGS:=-nostdlib

# output directory
ifeq ($(BUILD_MODE),debug)
BUILD_DIR:=$(shell pwd)/build/debug
else
BUILD_DIR:=$(shell pwd)/build/normal
endif

PREFIX=/opt/riscv/bin
TARGET_ARCH?=riscv32
HOST?=$(PREFIX)/$(TARGET_ARCH)-unknown-elf

# toolchain params
CC=$(HOST)-gcc
AS=$(HOST)-as

PROJECT_DIR=${shell pwd}
DEST_DIR?=${PROJECT_DIR}/release

IMAGE_NAME = ${DEST_DIR}/sal_os$(TARGET_ARCH).elf

LINKER_SCRIPT=$(BUILD_DIR)/linker.ld

MODULES=$(TARGET_ARCH)
ALL_OBJS=$(shell find ${BUILD_DIR} -name "*.o" -type f)

VPATH=.

MAIN_OBJS=$(BUILD_DIR)/kernel_boot.S.o $(BUILD_DIR)/kernel_main.o
export

.PHONY: all $(MODULES)

all: $(IMAGE_NAME)

$(IMAGE_NAME): $(MODULES) $(MAIN_OBJS)
	$(CC) -T ${LINKER_SCRIPT} -o $@ $(CFLAGS) $(ALL_OBJS) $(LIBFLAGS) -static-libgcc -lgcc

${LINKER_SCRIPT}: ;

clean:
	rm -f $(BUILD_DIR)/*
	rm -f $(IMAGE_NAME)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(BUILD_DIR)
	$(CC) -c $^ -o $@ $(CFLAGS)

$(BUILD_DIR)/%.S.o: %.S
	mkdir -p $(BUILD_DIR)
	$(AS) $^ -o $@ $(ASFLAGS)

print-%:
	@echo $* = $($*)