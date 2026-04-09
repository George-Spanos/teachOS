SECTIONS {
    . = 0x8000;
    .text : {
        *(.vector_table)
        *(.text)
    }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}
