DEPDIR=.d
$(shell mkdir -p $(DEPDIR) >/dev/null)

TARGET_ARCH?=riscv32
PROJECT_DIR=${shell pwd}
ARCH_DIR=${PROJECT_DIR}/src/arch/${TARGET_ARCH}


DEST_DIR?=${PROJECT_DIR}/release
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOT_DIR=$(EXEC_PREFIX)/boot
INCLUDE_DIR=$(PREFIX)/include
LIB_DIR=$(PREFIX)/lib
ASM_DIR?=asm

HOST?=${TARGET_ARCH}-unknown-elf
CC=$(HOST)-gcc
AS=$(HOST)-as

# Declaring some options for building
CFLAGS=-O0 #-g
CFLAGS:=$(CFLAGS) -std=gnu99 -ffreestanding -fbuiltin -Wall -Wextra -mabi=ilp32
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
CPPFLAGS:=-D_kernel_code -I$(INCLUDE_DIR)
LIBFLAGS:=-nostdlib
#ASFLAGS:=-gstabs+

C_SRC_FILES=$(shell find . -type f -name "*.c")
ASM_SRC_FILES=$(shell find . -type f -name "*.S")
KERNEL_OBJS?=$(ASM_SRC_FILES:.S=.S.o)
KERNEL_OBJS+=$(C_SRC_FILES:.c=.o)

LINKER_SCRIPT=${ARCH_DIR}/linker.ld

ALL_OBJS=\
$(KERNEL_OBJS) 

IMAGE_NAME = ${DEST_DIR}/sphinx_$(TARGET_ARCH).elf

.PHONY: all clean print install-headers install-kernel install
.SUFFIXES: .o .S .c .S.o

.SECONDARY:

all: $(IMAGE_NAME)

$(IMAGE_NAME): ${LINKER_SCRIPT} $(ALL_OBJS)
	$(CC) -T ${LINKER_SCRIPT} -o $@ $(CFLAGS) $(ALL_OBJS) $(LIBFLAGS)

%.o: %.c
	mkdir -p $(shell dirname $(DEPDIR)/$*.Td)
	$(CC) -c $< -o $@ $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS)
	mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

%.o: %.S
	$(AS) $< -o $@ $(ASFLAGS)

%.S.o: %.s
	$(AS) $< -o $@ $(ASFLAGS)

install: install-headers install-kernel

install-kernel:
	mkdir -p $(DEST_DIR)$(BOOT_DIR)
	cp $(IMAGE_NAME) $(DEST_DIR)$(BOOT_DIR)

install-headers:
	mkdir -p $(DEST_DIR)$(INCLUDE_DIR)
	cp -rfp include/* $(DEST_DIR)$(INCLUDE_DIR)

clean:
	rm -f $(KERNEL_OBJS)
	rm -rf $(DEPDIR)
	rm -f $(IMAGE_NAME)

print-%:
	@echo $* = $($*)

$(DEPDIR)/%.d: ;

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS))))
