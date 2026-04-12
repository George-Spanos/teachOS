#include "timer.h"
#include "gpio.h"
#include "scheduler.h"
#include "uart.h"
#include "error.h"
#include "heap.h"
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

void test_heap() {
  heap_init();
  void *a = kmalloc(100);
  void *b = kmalloc(200);
  heap_dump();
  kfree(a);
  heap_dump();
}

void test_heap_2() {
  heap_init();
  void *a = kmalloc(100);
  void *b = kmalloc(200);
  heap_dump();
  uart_puts("----\n");
  kfree(a);
  heap_dump();
  uart_puts("----\n");
  void *c = kmalloc(100);
  kfree(b);
  void *d = kmalloc(100);
  uart_puts("----\n");
  heap_dump();
}

void main() {
  uart_init();
  // LOGGING
  uart_puts("UART INIT\n");
  timer_init();
  test_heap_2();
  // int r = gpio_set_output(17);
  // if (r) {
  //   uart_puts("GPIO OUTPUT SET 17");
  // }

  // framebuffer_init();
  // draw_string(100, 100, "Hello Kostakis Kailas", 0x00FFFFFF);
  // error_t r = scheduler_create_task(task_a);
  // r = scheduler_create_task(task_b);
  // scheduler_start();
}
