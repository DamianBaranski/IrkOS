#include "types.h"

char hello[] = "Hello world!!!";

void *memset(void *buffer, char c, int num) {
  int i;
  for (i = 0; i < num; i++) {
    *((char *)(buffer + i)) = c;
  }
}

void main(void *mbd, uint32_t magic) {
  uint8_t i = 0;
  uint16_t *videoram = (uint16_t *)0xB8000; // 0xB0000 for monochrome monitors
  memset(videoram, 0, 16000);

  while (hello[i] != '\0') {
    videoram[i] = hello[i] | 0x0F00;
    i++;
  }

  while (1)
    ; // just spin
}
