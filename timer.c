#include "uart.h"
volatile unsigned int *CS = (unsigned int *)0x20003000;
volatile unsigned int *CLO = (unsigned int *)0x20003004;
volatile unsigned int *C1 = (unsigned int *)0x20003010;
volatile unsigned int *IRQ_ENABLE_1 = (unsigned int *)0x2000B210;

// 0.5s = 500.000 μs
#define INTERVAL 1000000

void (*callback)();
void timer_init(void (*cb)()) {
  *C1 = *CLO + INTERVAL;
  *IRQ_ENABLE_1 = (1 << 1);
  callback = cb;
}

void handle_irq() {
  if (*CS & (1 << 1)) {
    uart_puts("-- Interrupt --");
    callback();
    *CS = (1 << 1);
    *C1 = *CLO + INTERVAL;
  }
}
