.section .vector_table, "ax"
.global vector_table
vector_table:
    ldr pc, reset_addr
    ldr pc, undef_addr
    ldr pc, svc_addr
    ldr pc, prefetch_addr
    ldr pc, data_addr
    ldr pc, reserved_addr    
    ldr pc, irq_addr
    ldr pc, fiq_addr
reset_addr:     .word _start
undef_addr:     .word hang
svc_addr:       .word hang
prefetch_addr:  .word hang
reserved_addr:  .word hang
data_addr:      .word hang
irq_addr:       .word irq_handler
fiq_addr:       .word hang

.section .text
.global _start
_start:
    LDR SP, =0x100000
    LDR r0, =vector_table
    LDR r1, =0x00
    LDR r2, =vector_table + 64
copy_loop:
    LDR r3, [r0]
    STR r3, [r1]
    ADD r0, r0, #4
    ADD r1, r1, #4
    CMP r0, r2
    BLT copy_loop
    MRS r0, cpsr
    BIC r0, r0, #0x1F
    ORR r0, r0, #0x12
    MSR cpsr_c, r0
    LDR SP, =0x90000
    BIC r0, r0, #0x1F
    ORR r0, r0, #0x13
    MSR cpsr_c, r0
    LDR SP, =0x100000
    MRS r0, cpsr
    BIC r0, r0, #0x80
    MSR cpsr_c, r0
    BL main
    B .
irq_handler:
    SUB lr, lr, #4
    STMFD sp!, {r0-r12, lr}
    BL handle_irq
    LDMFD sp!, {r0-r12, pc}^
hang:
    b hang
