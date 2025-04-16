
# dirs
FS		:=./fs
BUILD	:=./build
KERNEL	:=./kernel
SCRIPTS	:=./scripts
INCLUDE	:=./include

# flags
CROSS_COMPILE=riscv64-unknown-linux-gnu-

# tools using the cross-compiler
CC		:= $(CROSS_COMPILE)gcc
CXX 	:= $(CROSS_COMPILE)g++
AS 		:= $(CROSS_COMPILE)as
LD 		:= $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
AR 		:= $(CROSS_COMPILE)ar
SIZE 	:= $(CROSS_COMPILE)size

#about machine
ISA		:= rv64imafdc
ABI		:= lp64

# Define flags
CF := -march=$(ISA) -mabi=$(ABI) -mcmodel=medany -fno-builtin -ffunction-sections 
CF += -fdata-sections -nostartfiles -nostdlib -nostdinc -static -Wall -g 
CFLAGS := $(CF) -I $(INCLUDE)
LDFLAGS := -nostdlib -static -T $(KERNEL)/link.ld

# Kernel source file
KERNEL_C_SRCS = $(wildcard kernel/*.c)
KERNEL_AS_SRCS = $(wildcard kernel/*.S)

# kernel target file
KERNEL_C_OBJS = $(patsubst kernel/%.c, build/kernel/%.o, $(KERNEL_C_SRCS))
KERNEL_AS_OBJS = $(patsubst kernel/%.S, build/kernel/%.o, $(KERNEL_AS_SRCS))

# combine all objs
OBJS = $(KERNEL_C_OBJS) $(KERNEL_AS_OBJS)

TARGET_ELF = build/kernel.elf
TARGET_BIN = build/kernel.bin

TARGET = $(TARGET_BIN) $(TARGET_ELF)
export KTARGET := $(TARGET)

.PHONY: clean img kernel

all: kernel

# build kernel
kernel: build_dir $(TARGET)

# LD
$(TARGET_ELF): $(OBJS)
	@echo "LD $(TARGET_ELF)"
	@$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET_ELF)

# BIN
$(TARGET_BIN): $(TARGET_ELF)
	@echo "COPY $(TARGET_BIN)"
	@$(OBJCOPY) -O binary $(TARGET_ELF) $(TARGET_BIN)

# make build dir
build_dir:
# @echo "CREATE build DIR"
	@mkdir -p build
	@mkdir -p build/kernel

# rule to compile .c
build/kernel/%.o: kernel/%.c
	@echo "CC $@"
	@$(CC) $(CFLAGS) -c $< -o $@
# rule to compile .S
build/kernel/%.o: kernel/%.S
	@echo "AS $@"
	@$(CC) $(CFLAGS) -c $< -o $@


# includes
include scripts/firmware.mk
include scripts/qemu.mk

clean:
	rm -rf build

img:
	@echo "TODO"