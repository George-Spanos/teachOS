#include "framebuffer.h"
#include "font.h"

#define FONT_SCALE 4

void draw_pixel(int x, int y, unsigned int color) {
  framebuffer[y * 1024 + x] = color;
}

void draw_char(int x, int y, char c, unsigned int color) {
  unsigned char *cb = font[c];
  for (int row = 0; row < 8; row++) {
    for (int col = 7; col >= 0; col--) {
      if (*cb & (1 << col)) {
        // draw_pixel(x + (7 -col ), y + row, color);
        for (int sy = 0; sy < FONT_SCALE; sy++) {
          for (int sx = 0; sx < FONT_SCALE; sx++) {
            draw_pixel(x + (7 - col) * FONT_SCALE + sx, y + row * FONT_SCALE + sy, color);
          }
        }
      }
    }
    cb++;
  }
}

void draw_string(int x, int y, const char *s, unsigned int color) {
  while (*s != '\0') {
    draw_char(x, y, *s, color);
    s++;
    x += 8 * FONT_SCALE;
  }
}

void draw_rect(int x, int y, int width, int height, unsigned int color) {
  for (int j = y; j < y + height; j++) {
    for (int i = x; i < x + width; i++) {
      draw_pixel(i, j, color);
    }
  }
}
