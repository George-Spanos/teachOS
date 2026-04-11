#ifndef TIMER_H
#define TIMER_H

// 1s
#define INTERVAL 100000

extern volatile unsigned int *CS;
extern volatile unsigned int *C1;
extern volatile unsigned int *CLO;
void timer_init();

#endif
