#ifndef IO_H
#define IO_H
#include "types.h"

static inline void outb(uint16_t port, uint8_t val) {
  asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

#endif
