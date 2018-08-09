include makefile.defines

TARGET_ARCH?=riscv32
HOST?=$(TARGET_ARCH)-unknown-elf

PROJECT_DIR=${shell pwd}
DEST_DIR?=${PROJECT_DIR}/release

IMAGE_NAME = ${DEST_DIR}/sphinx_$(TARGET_ARCH).elf

LINKER_SCRIPT=$(BUILD_DIR)/linker.ld

MODULES=$(TARGET_ARCH)
ALL_OBJS=$(shell find ${BUILD_DIR} -name "*.o" -type f)

VPATH=.

MAIN_OBJS=$(BUILD_DIR)/kernel_boot.S.o $(BUILD_DIR)/kernel_main.o
export

.PHONY: all $(MODULES)

all: $(IMAGE_NAME)

$(IMAGE_NAME): $(MODULES) $(MAIN_OBJS)
	$(CC) -T ${LINKER_SCRIPT} -o $@ $(CFLAGS) $(ALL_OBJS) $(LIBFLAGS)

$(TARGET_ARCH):
	cd arch/$(TARGET_ARCH); \
	make --include-dir=$(PROJECT_DIR)

${LINKER_SCRIPT}: ;

include makefile.rules_general

clean:
	rm -f $(BUILD_DIR)/*
	rm -f $(IMAGE_NAME)
