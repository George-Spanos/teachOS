.global _start

_start:
    LDR SP, =0x8000
    BL main
    B .
