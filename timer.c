// IRQ interrupts timer initialization
#include "timer.h"

volatile unsigned int *CS = (unsigned int *)0x20003000;
volatile unsigned int *CLO = (unsigned int *)0x20003004;
volatile unsigned int *C1 = (unsigned int *)0x20003010;
volatile unsigned int *IRQ_ENABLE_1 = (unsigned int *)0x2000B210;


void timer_init() {
  *C1 = *CLO + INTERVAL;
  *IRQ_ENABLE_1 = (1 << 1);
}
