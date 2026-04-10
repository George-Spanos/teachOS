#include "framebuffer.h"
#include "gpio.h"
#include "timer.h"
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

void main() {
  uart_init();
  // LOGGING
  uart_puts("UART INIT\n");
  int r = gpio_set_output(17);
  if (r) {
    uart_puts("GPIO OUTPUT SET 17");
  }
  // timer_init(toggle_led);

  framebuffer_init();
  // draw_string(100, 100, "Hello Kostakis Kailas", 0x00FFFFFF);
}
