#ifndef MAILBOX_H
#define MAILBOX_H
extern volatile unsigned int mailbox_buffer[32]; 
int mailbox_call(unsigned int address, unsigned int channel);
#endif
