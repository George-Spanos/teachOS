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
    @ Βήμα 1: Σώσε r0, CPSR, pc στο IRQ stack
    SUB lr, lr, #4
    STMFD sp!, {r0-r3, lr}      @ σώσε r0-r3 και pc στο IRQ stack
    MRS r0, SPSR                @ r0 = CPSR του task
    MOV r1, sp                  @ r1 = διεύθυνση IRQ stack

    @ Βήμα 2: Άλλαξε σε SVC mode (IRQs off)
    MRS r2, cpsr
    BIC r2, r2, #0x1F
    ORR r2, r2, #0x93
    MSR cpsr_c, r2

    @ βρες που βρίσκεται το context του running task
    LDR r2, =current_task_idx
    LDR r2, [r2]
    MOV r3, #80
    MUL r2, r2, r3
    LDR r3, =tasks
    ADD r3, r3, r2
    ADD r3, r3, #4              @ r3 = &context[0]
    @ σώσε τα τωρινά registers στο context
    STR r4,  [r3, #16]
    STR r5,  [r3, #20]
    STR r6,  [r3, #24]
    STR r7,  [r3, #28]
    STR r8,  [r3, #32]
    STR r9,  [r3, #36]
    STR r10, [r3, #40]
    STR r11, [r3, #44]
    STR r12, [r3, #48]
    STR sp,  [r3, #52]          @ context[13] = sp
    STR lr,  [r3, #56]          @ context[14] = lr
    STR r0,  [r3, #64]          @ context[16] = CPSR (ήταν στο r0)
    @ μετέφερε τιμές από το irq stack στο context
    LDR r4, [r1]
    STR r4, [r3, #0]            @ context[0] = r0
    LDR r4, [r1, #4]
    STR r4, [r3, #4]            @ context[1] = r1
    LDR r4, [r1, #8]
    STR r4, [r3, #8]            @ context[2] = r2
    LDR r4, [r1, #12]
    STR r4, [r3, #12]           @ context[3] = r3
    LDR r4, [r1, #16]
    STR r4, [r3, #60]           @ context[15] = pc
    bl schedule
    CMP r0, #0
    BEQ restore_current
    B load_context
restore_current:
    LDR r0, =current_task_idx
    LDR r0, [r0]
    MOV r1, #80
    MUL r0, r0, r1
    LDR r1, =tasks
    ADD r0, r1, r0
    ADD r0, r0, #4              @ r0 = &context[0]
load_context:
    @ r0 = &context[0] του νέου task

    @ Φόρτωσε sp, lr
    LDR sp,  [r0, #52]
    LDR lr,  [r0, #56]

    @ Σώσε τον saved pc στο stack του νέου task (θα τον χρειαστούμε στο τέλος)
    LDR r1,  [r0, #60]
    STMFD sp!, {r1}

    @ Φόρτωσε r4-r12
    LDR r4,  [r0, #16]
    LDR r5,  [r0, #20]
    LDR r6,  [r0, #24]
    LDR r7,  [r0, #28]
    LDR r8,  [r0, #32]
    LDR r9,  [r0, #36]
    LDR r10, [r0, #40]
    LDR r11, [r0, #44]
    LDR r12, [r0, #48]

    @ Φόρτωσε r1-r3 (r0 ακόμα κρατάει τη βάση)
    LDR r1,  [r0, #4]
    LDR r2,  [r0, #8]
    LDR r3,  [r0, #12]

    @ Φόρτωσε r0 τελευταίο — μετά χάνεις τη βάση
    LDR r0,  [r0, #0]

    @ Ενεργοποίησε IRQs (SVC mode, bit 7 = 0)
    MSR cpsr_c, #0x13

    @ Πήδα στον saved pc
    LDMFD sp!, {pc}

hang:
    b hang
