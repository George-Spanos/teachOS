#include "timer.h"
#include "gpio.h"
#include "scheduler.h"
#include "uart.h"
#include "error.h"

int on = 0;

void toggle_led() {
  if (!on) {
    gpio_set_high(17);
    on = 1;
  } else {
    gpio_set_low(17);
    on = 0;
  }
}

void task_a() {
  while (1) {
    uart_puts("Task A\n");
  }
}

void task_b() {
  while (1) {
    uart_puts("Task B\n");
  }
}
void main() {
  uart_init();
  // LOGGING
  uart_puts("UART INIT\n");
  timer_init();
  // int r = gpio_set_output(17);
  // if (r) {
  //   uart_puts("GPIO OUTPUT SET 17");
  // }

  // framebuffer_init();
  // draw_string(100, 100, "Hello Kostakis Kailas", 0x00FFFFFF);
  error_t r = scheduler_create_task(task_a);
  r = scheduler_create_task(task_b);
  scheduler_start();
}
