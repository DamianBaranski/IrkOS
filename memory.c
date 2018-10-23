#include "memory.h"

void *memset(void *buffer, uint8_t value, uint32_t num) {
  int i;
  for (i = 0; i < num; i++) {
    *((char *)(buffer + i)) = value;
  }
}

