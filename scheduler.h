#ifndef SCHEDULER_H

#define SCHEDULER_H
#include <stdint.h>

// assembly function for context switching. Mandatory for working with CPU registers.
extern void context_switch(uint32_t *old_context, uint32_t *new_context);
extern void context_load(uint32_t *context);
void yield();
void scheduler_start();
int scheduler_create_task(void (*handler)());
typedef enum {
  TASK_UNUSED,
  TASK_READY,
  TASK_RUNNING,
  TASK_FINISHED
} task_state_t;

typedef struct {
  task_state_t state;
  uint32_t context[10];
  void (*handler)();
  uint32_t* stack;
} task_t;
#endif
