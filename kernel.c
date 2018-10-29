#include "gdt.h"
#include "types.h"
#include "vga.h"

char hello[] = "Hello world!!!";

void main(void *mbd, uint32_t magic) {
  vga_init();
  vga_cls();
  for (int i = 0; i < 30; i++)
    kprintf("hello: %d %s\n", i, hello);

  while (1)
    ; // just spin
}
