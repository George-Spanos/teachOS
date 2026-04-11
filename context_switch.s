.global context_switch
context_switch:
    str r4, [r0, #0]
    str r5, [r0, #4]
    str r6, [r0, #8]
    str r7, [r0, #12]
    str r8, [r0, #16]
    str r9, [r0, #20]
    str r10, [r0, #24]
    str r11, [r0, #28]
    str sp, [r0, #32]
    str lr, [r0, #36]
    ldr r4, [r1, #0]
    ldr r5, [r1, #4]
    ldr r6, [r1, #8]
    ldr r7, [r1, #12]
    ldr r8, [r1, #16]
    ldr r9, [r1, #20]
    ldr r10, [r1, #24]
    ldr r11, [r1, #28]
    ldr sp, [r1, #32]
    ldr lr, [r1, #36]
    bx lr

.global context_load
context_load:
    ldr r4, [r0, #0]
    ldr r5, [r0, #4]
    ldr r6, [r0, #8]
    ldr r7, [r0, #12]
    ldr r8, [r0, #16]
    ldr r9, [r0, #20]
    ldr r10, [r0, #24]
    ldr r11, [r0, #28]
    ldr sp, [r0, #32]
    ldr lr, [r0, #36]
    bx lr
