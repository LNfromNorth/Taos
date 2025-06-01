OUTPUT_ARCH("riscv")
OUTPUT_FORMAT("elf64-littleriscv")
ENTRY(_start)

BASE_ADDR = 0x80400000;

SECTIONS
{
    /* text: test code section */
    . = BASE_ADDR;
    _skerenl = .;

    .text : ALIGN(0x1000) {
        _stext = .;
        *(.text.entry)
        *(.text .text.*)
        . = ALIGN(4K);
        PROVIDE(_etext = .);
    }

    .rodata : ALIGN(0x1000) {
        _srodata = .;
        *(.rodata .rodata.*)
        _erodata = .;
    }

    .data : ALIGN(0x1000) {
        _sdata = .;
        *(.data .data.*)
        _edata = .;
    }

    .bss : ALIGN(0x1000) {
        _sbss = .;
        *(.bss.stack)
        *(.bss .bss.*)
        _ebss = .;
    }

    . = ALIGN(0x1000);
    PROVIDE(_ekernel = .);
}
