#ifndef HEAP_H
#define HEAP_H
#include <stdint.h>
#include "error.h"

#define HEAP_START 0x100000
#define HEAP_END 0x1C000000

typedef enum {
  ALLOCATED,
  FREE
} mem_status;

typedef struct {
  mem_status status;
  uint32_t size;
} header_t;

void *kmalloc(uint32_t size);
void kfree(void *addr);
error_t heap_init();
void heap_dump();
#endif
