.section .vector_table, "ax"
.global vector_table
vector_table:
    b _start              @ 0x00 Reset
    b hang                @ 0x04 Undefined
    b hang                @ 0x08 SVC
    b hang                @ 0x0C Prefetch Abort
    b hang                @ 0x10 Data Abort
    nop                   @ 0x14 Reserved
    b hang                @ 0x18 IRQ
    b hang                @ 0x1C FIQ

hang:
    b hang

.section .text
.global _start
_start:
    LDR SP, =0x100000
    LDR r0, =vector_table
    LDR r1, =0x00
    LDR r2, =vector_table + 32
copy_loop:
    LDR r3, [r0]
    STR r3, [r1]
    ADD r0, r0, #4
    ADD r1, r1, #4
    CMP r0, r2
    BLT copy_loop
    BL main
    B .
