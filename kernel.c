#include "uart.h"
#include "mailbox.h"

void main() {
  uart_init();
  
  // LOGGING
  uart_puts("Mantalakia\n");


  // READ AND PRINT LOOP
  // 
  // while (1) {
  //   char c = uart_getc();
  //   uart_putc(c);
  // }

  framebuffer_init();
  // draw_string(100, 100, "Hello Kostakis Kailas", 0x00FFFFFF);
}
