# qemu
QEMU=qemu-system-riscv64

# bios opensbi firmware
OPENSBI_BIN = opensbi/build/platform/generic/firmware/fw_jump.bin
# bootloader u-boot
UBOOT_BIN = u-boot/u-boot.bin

# kernel 
KERNEL_ELF = build/kernel.elf

QFLAGS  = -M virt
QFLAGS += -m 256M
QFLAGS += -nographic
# QFLAGS += -bios none
# QFLAGS += -kernel build/kernel.elf

QFLAGS_BIOS = -bios $(OPENSBI_BIN)

qemu: build/kernel.elf
	$(QEMU) $(QFLAGS) -kernel $(KERNEL_ELF)

qemu_bios: build/kernel.elf firmware
	$(QEMU) $(QFLAGS) $(QFLAGS_BIOS) -kernel $(KERNEL_ELF)

qemu_bl: build/kernel.elf firmware_u-boot
	$(QEMU) $(QFLAGS) $(QFLAGS_BIOS) -kernel $(UBOOT_BIN)