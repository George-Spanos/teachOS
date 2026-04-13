#include "error.h"
#include "timer.h"
#include "uart.h"
#include "v3d.h"

void main() {
  uart_init();
  // LOGGING
  uart_puts("UART INIT\n\r");
  timer_init();
  error_t r =  v3d_init();
  if(r == SUCCESS) {
    uart_puts("V3D INIT");
  }else {
    uart_puts(error_to_string(r));
  }
}
