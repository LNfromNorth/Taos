# qemu
QEMU=qemu-system-riscv64

# bios opensbi firmware
OPENSBI_JUMP = opensbi/build/platform/generic/firmware/fw_jump.bin
OPENSBI_PAYLOAD = opensbi/build/platform/generic/firmware/fw_payload.bin
# bootloader u-boot
UBOOT_BIN = u-boot/u-boot.bin
# Disk location
DISK_IMG = build/disk.img

# kernel 
KERNEL_ELF = build/kernel.elf

QFLAGS  = -M virt
QFLAGS += -m 256M
QFLAGS += -nographic
QFLAGS += -global virtio-mmio.force-legacy=false
QFLAGS += -drive file=$(DISK_IMG),if=none,format=raw,id=hd0
QFLAGS += -device virtio-blk-device,drive=hd0
QFLAGS += -d guest_errors
# QFLAGS += -bios none
# QFLAGS += -kernel build/kernel.elf

QFLAGS_BIOS = -bios $(OPENSBI_JUMP)

QFLAGS_BL = -bios $(OPENSBI_PAYLOAD)
QFLAGS_BL += -device loader,file=./build/kernel.uimg,addr=0x80400000

qemu: kernel
	$(QEMU) $(QFLAGS) -kernel $(KERNEL_ELF)

qemug: kernel
	$(QEMU) $(QFLAGS) -s -S -kernel $(KERNEL_ELF)

qemu_bios: kernel firmware
	$(QEMU) $(QFLAGS) $(QFLAGS_BIOS) -kernel $(KERNEL_ELF)

qemu_bl: kernel firmware_u-boot
	$(QEMU) $(QFLAGS) $(QFLAGS_BL) -kernel $(UBOOT_BIN)
