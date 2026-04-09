#ifndef MAILBOX_H
#define MAILBOX_H
extern unsigned int *framebuffer;
int mailbox_call(unsigned int address, unsigned int channel);
void framebuffer_init();
void draw_pixel(int x, int y, unsigned int color);
void draw_rect(int x, int y, int width, int height, unsigned int color);
void draw_char(int x, int y, char c, unsigned int color);
void draw_string(int x, int y, const char *s, unsigned int color);
#endif
