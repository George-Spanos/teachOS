volatile unsigned int *READ = (unsigned int *)0x2000B880;
volatile unsigned int *STATUS = (unsigned int *)0x2000B898;
volatile unsigned int *WRITE = (unsigned int *)0x2000B8A0;

volatile unsigned int __attribute__((aligned(16))) mailbox_buffer[32];

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
