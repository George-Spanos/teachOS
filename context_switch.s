.global context_switch
context_switch:
    str r4,  [r0, #16]
    str r5,  [r0, #20]
    str r6,  [r0, #24]
    str r7,  [r0, #28]
    str r8,  [r0, #32]
    str r9,  [r0, #36]
    str r10, [r0, #40]
    str r11, [r0, #44]
    str sp,  [r0, #52]
    str lr,  [r0, #56]
    ldr r4,  [r1, #16]
    ldr r5,  [r1, #20]
    ldr r6,  [r1, #24]
    ldr r7,  [r1, #28]
    ldr r8,  [r1, #32]
    ldr r9,  [r1, #36]
    ldr r10, [r1, #40]
    ldr r11, [r1, #44]
    ldr sp,  [r1, #52]
    ldr lr,  [r1, #56]
    bx lr

.global context_load
context_load:
    ldr r4,  [r0, #16]
    ldr r5,  [r0, #20]
    ldr r6,  [r0, #24]
    ldr r7,  [r0, #28]
    ldr r8,  [r0, #32]
    ldr r9,  [r0, #36]
    ldr r10, [r0, #40]
    ldr r11, [r0, #44]
    ldr sp,  [r0, #52]
    ldr lr,  [r0, #60]
    bx lr
