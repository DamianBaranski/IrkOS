#include "gdt.h"
#include "types.h"
#include "vga.h"

void main(void *mbd, uint32_t magic) {
  vga_init();
  vga_cls();
  gdt_init();

  while (1)
    ; // just spin
}
