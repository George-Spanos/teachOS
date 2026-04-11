#include "error.h"


char* error_to_string(error_t error_code) {
  switch(error_code) {
    case MAILBOX_INIT_ERROR:
      return "MAILBOX INIT ERROR";
    case FRAMEBUFFER_INIT_ERROR:
      return "FRAMEBUFFER INIT ERROR";
    case CREATE_TASK_ERROR:
      return "CREATE TASK ERROR";
    default:
      return "UNKNOWN ERROR CODE";
  }
}
