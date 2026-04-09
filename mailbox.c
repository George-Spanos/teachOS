volatile unsigned int *READ = (unsigned int *)0x2000B880;
volatile unsigned int *STATUS = (unsigned int *)0x2000B898;
volatile unsigned int *WRITE = (unsigned int *)0x2000B8A0;

volatile unsigned int __attribute__((aligned(16))) mailbox_buffer[32];
unsigned int *framebuffer;

int mailbox_call(unsigned int address, unsigned int channel) {
  while (*STATUS & (1 << 31))
    ;
  *WRITE = address | channel;
  while (1) {
    while (*STATUS & (1 << 30))
      ;
    unsigned int response = *READ;
    if ((response & 0x0F) == channel) {

      if ((response & 0xFFFFFFF0) == address) {
        return 1;
      }
      return 0;
    }
  }
}

void framebuffer_init() {
  mailbox_buffer[0] = 35 * 4;     // μέγεθος buffer σε bytes
  mailbox_buffer[1] = 0x00000000; // request

  // Set physical size
  mailbox_buffer[2] = 0x00048003; // tag ID
  mailbox_buffer[3] = 8;          // μέγεθος δεδομένων (2 × 4 bytes)
  mailbox_buffer[4] = 0;          // request code
  mailbox_buffer[5] = 1024;       // πλάτος
  mailbox_buffer[6] = 600;        // ύψος

  // Set virtual size
  mailbox_buffer[7] = 0x00048004; // tag ID
  mailbox_buffer[8] = 8;
  mailbox_buffer[9] = 0;
  mailbox_buffer[10] = 1024;
  mailbox_buffer[11] = 600;

  // Set depth
  mailbox_buffer[12] = 0x00048005; // tag ID
  mailbox_buffer[13] = 4;          // μέγεθος δεδομένων (1 × 4 bytes)
  mailbox_buffer[14] = 0;
  mailbox_buffer[15] = 32; // 32 bits ανά pixel

  // Allocate buffer
  mailbox_buffer[16] = 0x00040001; // tag ID
  mailbox_buffer[17] = 8;
  mailbox_buffer[18] = 0;
  mailbox_buffer[19] = 16; // alignment
  mailbox_buffer[20] = 0;  // εδώ ο GPU θα γράψει το μέγεθος

  // End tag
  mailbox_buffer[21] = 0x00000000;

  mailbox_call((unsigned int)mailbox_buffer, 8);
  framebuffer = (unsigned int *)(mailbox_buffer[19] & 0x3FFFFFFF);
}

void draw_pixel(int x, int y, unsigned int color) {
  framebuffer[y * 1024 + x] = color;
}

void draw_rect(int x, int y, int width, int height, unsigned int color) {
  for (int j = y; j < y + height; j++) {
    for (int i = x; i < x + width; i++) {
      draw_pixel(i, j, color);
    }
  }
}
