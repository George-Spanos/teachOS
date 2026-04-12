#include <stdint.h>

char *uint_to_dec(uint32_t value) {
  
    static char buf[11];
    int i = 10;
    buf[i] = '\0';
    if (value == 0) {
        buf[--i] = '0';
        return &buf[i];
    }
    while (value > 0) {
        buf[--i] = '0' + (value % 10);
        value /= 10;
    }
    return &buf[i];
}

char *uint_to_hex(uint32_t value) {
  static char buf[11];
  char hex_chars[] = "0123456789ABCDEF";
  buf[0] = '0';
  buf[1] = 'x';
  for (int i = 9; i >= 2; i--) {
    buf[i] = hex_chars[value & 0xF];
    value >>= 4;
  }
  buf[10] = '\0';
  return buf;
}

