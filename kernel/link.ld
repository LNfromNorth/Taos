OUTPUT_ARCH("riscv")
OUTPUT_FORMAT("elf64-littleriscv")
ENTRY(_start)

PHDRS{
    text PT_LOAD FLAGS(5);
    data PT_LOAD FLAGS(6);
    bss PT_LOAD FLAGS(6);
}

SECTIONS
{
    /* text: test code section */
    . = 0x80400000;
    start = .;

    .text : {
        stext = .;
            *(.text.entry)
            *(.text .text.*)
            . = ALIGN(4K);
            etext = .;
    } :text

    .data : {
        sdata = .;
        *(.data .data.*)
        edata = .;
    } :data

    .bss : {
        sbss = .;
        *(.bss .bss.*)
        ebss = .;
    } :bss

    PROVIDE(end = .);
}
