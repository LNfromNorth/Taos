# firmawre compile makefile
# opensbi & u-boot
CROSS_COMPILE ?= riscv64-linux-gnu-

UBOOT_DIR ?= u-boot
OPENSBI_DIR ?= opensbi

PLATFORM ?= generic
PLATFORM_RISCV_XLEN ?= 64
FW_TEXT_START ?= 0x80000000

SBIFLAG  = PLATFORM=$(PLATFORM) 
SBIFLAG += PLATFORM_RISCV_XLEN=$(PLATFORM_RISCV_XLEN) 
SBIFLAG += CROSS_COMPILE=$(CROSS_COMPILE)
SBIFLAG += FW_TEXT_START=$(FW_TEXT_START)

# for fw jump mode
FW_JUMP_ADDR ?= 0x80200000
# for fw payload mode
FW_PAYLOAD_PATH=../u-boot/u-boot.bin

firmware: opensbi

firmware_u-boot: u-boot opensbi_u-boot

opensbi_u-boot:
	$(MAKE) -C $(OPENSBI_DIR) $(SBIFLAG) FW_PAYLOAD_PATH=$(FW_PAYLOAD_PATH)

opensbi:
	$(MAKE) -C $(OPENSBI_DIR) $(SBIFLAG) FW_JUMP_ADDR=$(FW_JUMP_ADDR)

clean_opensbi:
	$(MAKE) -C $(OPENSBI_DIR) clean
	rm -rf opensbi/build

u-boot:
	$(MAKE) -C $(UBOOT_DIR) qemu-riscv64_smode_defconfig
	$(MAKE) -C $(UBOOT_DIR) CROSS_COMPILE=$(CROSS_COMPILE) 

clean_u-boot:
	$(MAKE) -C $(UBOOT_DIR) clean


.PHONY: opensbi clean_opensbi u-boot clean_u-boot clean firmware