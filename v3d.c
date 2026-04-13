#include "error.h"
#include "mailbox.h"

volatile unsigned int *V3D_IDENT0 = (unsigned int*) 0x20C00000;
#define V3D_VERSION 0x02
#define V3D_ID_STR 0x443356

error_t v3d_init() {

  mailbox_buffer[0] = 7 * 4;      // buffer size in bytes
  mailbox_buffer[1] = 0x00000000; // request
  mailbox_buffer[2] = 0x00030012; // tagID
  mailbox_buffer[3] = 4;          // value buffer size
  mailbox_buffer[4] = 0;
  mailbox_buffer[5] = 1;
  // End tag
  mailbox_buffer[6] = 0x00000000;

  error_t r = mailbox_call((unsigned int)mailbox_buffer, 8);
  if (r == V3D_INIT_ERROR) {
    return V3D_INIT_ERROR;
  }
  int val = *V3D_IDENT0 >> 24 & 0xFF;
  if (val != V3D_VERSION) {
    return V3D_INIT_ERROR;
  }
  val = *V3D_IDENT0 & 0xFFFFFF;
  if (val != V3D_ID_STR) {
    return V3D_INIT_ERROR;
  }
  return SUCCESS;
}
