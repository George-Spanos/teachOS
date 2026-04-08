volatile unsigned int *DR = (unsigned int *)0x20201000;
volatile unsigned int *FR = (unsigned int *)0x20201018;
volatile unsigned int *IBRD = (unsigned int *)0x20201024;
volatile unsigned int *FBRD = (unsigned int *)0x20201028;
volatile unsigned int *LCRH = (unsigned int *)0x2020102c;
volatile unsigned int *CR = (unsigned int *)0x20201030;
volatile unsigned int *GPFSEL1 = (unsigned int *)0x20200004;

void uart_init() {
  *CR = 0x0;
  unsigned int sel;
  sel = *GPFSEL1;
  sel &= ~(7 << 12);
  sel |= (4 << 12);
  sel &= ~(7 << 15);
  sel |= (4 << 15);
  *GPFSEL1 = sel;
  *IBRD = 1;
  *FBRD = 40;
  *LCRH = (3 << 5);
  *CR = (1 << 0) | (1 << 8) | (1 << 9);
}
