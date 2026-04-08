volatile unsigned int *AUX_ENABLES  = (unsigned int *)0x20215004;
volatile unsigned int *AUX_MU_IO    = (unsigned int *)0x20215040;
volatile unsigned int *AUX_MU_IER   = (unsigned int *)0x20215044;
volatile unsigned int *AUX_MU_IIR   = (unsigned int *)0x20215048;
volatile unsigned int *AUX_MU_LCR   = (unsigned int *)0x2021504C;
volatile unsigned int *AUX_MU_MCR   = (unsigned int *)0x20215050;
volatile unsigned int *AUX_MU_LSR   = (unsigned int *)0x20215054;
volatile unsigned int *AUX_MU_CNTL  = (unsigned int *)0x20215060;
volatile unsigned int *AUX_MU_BAUD  = (unsigned int *)0x20215068;
volatile unsigned int *GPFSEL1      = (unsigned int *)0x20200004;

void uart_init() {
    unsigned int sel;

    sel = *GPFSEL1;
    sel &= ~(7 << 12);
    sel |= (2 << 12);
    *GPFSEL1 = sel;

    *AUX_ENABLES = 1;
    *AUX_MU_CNTL = 0;
    *AUX_MU_IER  = 0;
    *AUX_MU_LCR  = 3;
    *AUX_MU_MCR  = 0;
    *AUX_MU_BAUD = 270;
    *AUX_MU_CNTL = 3;
}

void uart_putc(char c) {
    while (!(*AUX_MU_LSR & 0x20));
    *AUX_MU_IO = c;
}

void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s);
        s++;
    }
}

void main() {
    uart_init();
    uart_puts("Hello from C on bare-metal George Spanos!\n");
    while (1);
}
