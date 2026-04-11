#include "scheduler.h"
#include "timer.h"
#include "uart.h"
#include <stddef.h>
#include <stdint.h>

#define MAX_TASKS 4
#define STACK_SIZE 256

task_t tasks[MAX_TASKS];
int current_task_idx = 0;
uint32_t stacks[MAX_TASKS][STACK_SIZE];

int scheduler_create_task(void (*handler)()) {
  for (int i = 0; i < MAX_TASKS; i++) {
    if (tasks[i].state == TASK_UNUSED) {
      tasks[i].state = TASK_READY;
      tasks[i].handler = handler;
      tasks[i].stack = stacks[i];
      tasks[i].context[13] = (uint32_t)&stacks[i][STACK_SIZE - 1];
      tasks[i].context[15] = (uint32_t)handler;
      tasks[i].context[16] = 0x13;
      return 0;
    }
  }
  return -1;
}

task_t *find_next_task() {

  int i = (current_task_idx + 1) % MAX_TASKS;
  int n = 0;
  task_t *next_task = &tasks[i];

  while (next_task->state != TASK_READY && n < MAX_TASKS) {
    i = (i + 1) % MAX_TASKS;
    n += 1;
    next_task = &tasks[i];
  }
  if (n == MAX_TASKS)
    return NULL;
  tasks[current_task_idx].state = TASK_READY;
  next_task->state = TASK_RUNNING;
  current_task_idx = i;
  return next_task;
}

uint32_t* schedule() {
  if (*CS & (1 << 1)) {
    uart_puts("SCHEDULE");
    *CS = (1 << 1);
    *C1 = *CLO + INTERVAL;
    task_t *next_task = find_next_task();
    if (next_task != NULL) {
      return next_task->context;
    }
    return NULL;
  }
  return NULL;
}

void scheduler_start() {
  tasks[0].state = TASK_RUNNING;
  current_task_idx = 0;
  context_load(tasks[0].context);
}
