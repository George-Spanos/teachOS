#include "mailbox.h"

unsigned int *framebuffer;

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
