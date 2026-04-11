#ifndef ERROR_H
#define ERROR_H

typedef enum {
  SUCCESS,
  MAILBOX_INIT_ERROR,
  FRAMEBUFFER_INIT_ERROR,
  CREATE_TASK_ERROR
} error_t;

char* error_to_string(error_t error_code);

#endif
