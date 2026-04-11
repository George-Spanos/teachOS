#ifndef MAILBOX_H
#define MAILBOX_H
#include "error.h"
extern volatile unsigned int mailbox_buffer[32]; 
error_t mailbox_call(unsigned int address, unsigned int channel);
#endif
