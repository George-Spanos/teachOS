volatile unsigned int *GPFSEL1 = (unsigned int*) 0x20200004;
volatile unsigned int *GPSET0 = (unsigned int*) 0x2020001C;
volatile unsigned int *GPCLR0 = (unsigned int*) 0x20200028;

#define GPIO_PIN 17

int gpio_set_output(int pin) {
  if (GPIO_PIN / 10 != 1) {
    return 1;
  }
  int shift_by = (GPIO_PIN % 10) *3;
  *GPFSEL1 &= ~(7 << shift_by);
  *GPFSEL1 |= (1 <<shift_by);
  return 1;
}

void gpio_set_high(int pin) {
  *GPSET0 = (1 << pin);
}

void gpio_set_low(int pin) {
  *GPCLR0 = (1 << pin);
}
