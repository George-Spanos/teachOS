#include "uart.h"
#include "mailbox.h"

void main() {
  uart_init();
  
  // LOGGING
  // uart_puts("Mantalakia\n");


  // READ AND PRINT LOOP
  // 
  // while (1) {
  //   char c = uart_getc();
  //   uart_putc(c);
  // }

  framebuffer_init();
  draw_rect(100, 100, 200, 150, 0x00FF0000);  // κόκκινο ορθογώνιο:w
}
