ASFLAGS:=-mabi=ilp32
CFLAGS:=$(CFLAGS) -mabi=ilp32 -Iinclude
RISCV_BOARD?=virt
VPATH:=src:board/$(RISCV_BOARD)

C_SRCS_FULL:=$(shell find src board/$(RISCV_BOARD) -type f -name "*.c")
ASM_SRCS_FULL:=$(shell find src board/$(RISCV_BOARD) -type f -name "*.S")

C_SRCS:=$(notdir $(C_SRCS_FULL))
ASM_SRCS:=$(notdir $(ASM_SRCS_FULL))

OBJ_FILES:=$(C_SRCS:%.c=$(BUILD_DIR)/%.o)
OBJ_FILES:=$(OBJ_FILES) $(ASM_SRCS:%.S=$(BUILD_DIR)/%.S.o)

.PHONY: all linker_script
all: $(OBJ_FILES) linker_script

linker_script:
	mkdir -p $(BUILD_DIR)
	cp board/$(RISCV_BOARD)/linker.ld $(BUILD_DIR)

include makefile.rules_general
