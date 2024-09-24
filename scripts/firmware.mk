# firmawre compile makefile
# opensbi & u-boot

UBOOT_DIR ?= u-boot
OPENSBI_DIR ?= opensbi
CROSS_COMPILE ?= riscv64-linux-gnu-
FW_JUMP ?= 0x80000000

firmware: u-boot opensbi

u-boot:
	$(MAKE) -C $(UBOOT_DIR) qemu-riscv64_smode_defconfig
	$(MAKE) -C $(UBOOT_DIR) CROSS_COMPILE=$(CROSS_COMPILE) 

clean_u-boot:
	$(MAKE) -C $(UBOOT_DIR) clean

opensbi:
	$(MAKE) -C $(OPENSBI_DIR) CROSS_COMPILE=$(CROSS_COMPILE) FW_JUMP=$(FW_JUMP)

clean_opensbi:
	$(MAKE) -C $(OPENSBI_DIR) clean

.PHONY: opensbi clean_opensbi u-boot clean_u-boot clean firmware
clean: clean_opensbi clean_u-boot