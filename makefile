# dirs
FS=./fs
BUILD=./build
KERNEL=./kernel
SCRIPTS=./scripts
INCLUDE=./include

# flags
CROSS_COMPILE=riscv64-linux-gnu-

# tools using the cross-compiler
CC		= $(CROSS_COMPILE)gcc
CXX 	= $(CROSS_COMPILE)g++
AS 		= $(CROSS_COMPILE)as
LD 		= $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
AR 		= $(CROSS_COMPILE)ar
SIZE 	= $(CROSS_COMPILE)size

# Define flags
CFLAGS = -nostdlib -I $(INCLUDE)
LDFLAGS = -T $(SCRIPTS)/link.ld

# Kernel source file
KERNEL_C_SRCS = $(wildcard kernel/*.c)
KERNEL_AS_SRCS = $(wildcard kernel/*.S)

# kernel target file
KERNEL_C_OBJS = $(patsubst kernel/%.c, build/kernel/%.o, $(KERNEL_C_SRCS))
KERNEL_AS_OBJS = $(patsubst kernel/%.S, build/kernel/%.o, $(KERNEL_AS_SRCS))

# combine all objs
OBJS = $(KERNEL_C_OBJS) $(KERNEL_AS_OBJS)

TARGET = build/kernel.elf

# build kernel
all: build_dir $(TARGET)

# LD
$(TARGET): $(OBJS)
	@echo "LD $(TARGET)"
	@$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET)

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

.PHONY: clean img
clean:
	rm -rf build

img:
	@echo "TODO"