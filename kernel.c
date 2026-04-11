#include "gpio.h"
#include "scheduler.h"
#include "uart.h"

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
    yield();
  }
}

void task_b() {
  while (1) {
    uart_puts("Task B\n");
    yield();
  }
}
void main() {
  uart_init();
  // LOGGING
  uart_puts("UART INIT\n");
  // int r = gpio_set_output(17);
  // if (r) {
  //   uart_puts("GPIO OUTPUT SET 17");
  // }
  // timer_init(toggle_led);

  // framebuffer_init();
  // draw_string(100, 100, "Hello Kostakis Kailas", 0x00FFFFFF);
  scheduler_create_task(task_a);
  scheduler_create_task(task_b);
  scheduler_start();
}
