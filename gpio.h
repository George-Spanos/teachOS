#ifndef GPIO_H
#define GPIO_H
extern volatile unsigned int *GPFSEL1;
int gpio_set_output(int pin);
void gpio_set_high(int pin);
void gpio_set_low(int pin);

#endif
