#include "gdt.h"
#include "pic.h"
#include "types.h"
#include "vga.h"

void main(void *mbd, uint32_t magic) {
  vga_init();
  vga_cls();
  gdt_init();
  pic_remap();
  while (1)
    ; // just spin
}
