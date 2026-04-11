#include "scheduler.h"
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
      tasks[i].context[9] = (uint32_t)handler;
      tasks[i].context[8] = (uint32_t)&stacks[i][STACK_SIZE - 1];
      return 0;
    }
  }
  return -1;
}

void yield() {
  int i = (current_task_idx + 1) % MAX_TASKS;
  int n = 0;
  task_t *next_task = &tasks[i];

  while (next_task->state != TASK_READY && n < MAX_TASKS) {
    i = (i + 1) % MAX_TASKS;
    n += 1;
    next_task = &tasks[i];
  }
  if (n == MAX_TASKS)
    return;
  tasks[current_task_idx].state = TASK_READY;
  next_task->state = TASK_RUNNING;
  uint32_t *old_context = tasks[current_task_idx].context;
  current_task_idx = i;
  context_switch(old_context, next_task->context);
}
void scheduler_start() {
    tasks[0].state = TASK_RUNNING;
    current_task_idx = 0;
    context_load(tasks[0].context);
}

