#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "error.h"

extern unsigned int *framebuffer;
error_t framebuffer_init();
#endif
