#include "heap.h"
#include "error.h"
#include "uart.h"
#include "utils.h"
#include <stddef.h>
#include <stdint.h>

error_t heap_init() {
  header_t *h = (header_t *)HEAP_START;
  h->size = HEAP_END - HEAP_START - sizeof(header_t);
  h->status = FREE;
  return SUCCESS;
}


header_t *find_next_header(header_t *prev_header) {
  if (prev_header == NULL) {
    return (header_t *)HEAP_START;
  }
  uint32_t next_header_addr =
      sizeof(header_t) + (uint32_t)prev_header + prev_header->size;
  if (next_header_addr >= HEAP_END) {
    return NULL;
  }
  return (header_t *)next_header_addr;
}

header_t *split_mem_block(header_t *header, uint32_t size) {
  if (header->size <= size || header->status == ALLOCATED) {
    return NULL;
  }
  uint32_t remaining_size = header->size - size - sizeof(header_t);
  header_t *first_block = header;
  first_block->size = size;
  first_block->status = ALLOCATED;
  uint32_t second_block_pos = (uint32_t)first_block + sizeof(header_t) + size;
  header_t *second_block = (header_t *)second_block_pos;
  second_block->size = remaining_size;
  second_block->status = FREE;
  return first_block;
}
// when we free code blocks there is a chance we end up with consecutive free blocks
// the following function merges them
void coalesce() {
  header_t *h1 = find_next_header(NULL);
  header_t *h2 = find_next_header(h1);
  while (h2 != NULL) {
    if (h1->status == FREE && h2->status == FREE) {
      h1->size = h1->size + h2->size + sizeof(header_t);
      h2 = find_next_header(h1);
    } else {
      h1 = h2;
      h2 = find_next_header(h2);
    }
  }
}

char *heap_status_to_str(int status) {
  switch (status) {
  case ALLOCATED:
    return "ALLOCATED";
  case FREE:
    return "FREE";
  default:
    return NULL;
  }
}

void print_heap_block(header_t *header) {
  uart_puts("addr=");
  uart_puts(uint_to_hex((uint32_t)header));
  uart_puts(" size=");
  uart_puts(uint_to_dec(header->size));
  uart_puts(" status=");
  uart_puts(heap_status_to_str(header->status));
  uart_puts("\n");
}

void heap_dump() {
  header_t *h = find_next_header(NULL);
  while (h != NULL) {
    print_heap_block(h);
    h = find_next_header(h);
  }
}
void *kmalloc(uint32_t size) {
  header_t *h = find_next_header(NULL);
  while (h !=NULL && (h->size < size || h->status == ALLOCATED)) {
    h = find_next_header(h);
  }
  
  if (h == NULL)
    return NULL;

  if (h->size == size) {
    h->status = ALLOCATED;
    return (void*)((uint32_t)h + (uint32_t)sizeof(header_t));
  }
  return (void*)((uint32_t)split_mem_block(h, size) + (uint32_t)sizeof(header_t));
}

void kfree(void *addr) {
  uint32_t header_addr = (uint32_t)addr - (uint32_t)sizeof(header_t);
  header_t *h = (header_t*) header_addr;
  h->status = FREE;
  coalesce();
}
