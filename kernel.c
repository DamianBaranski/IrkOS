#include "types.h"
#include "vga.h"

char hello[] = "Hello world!!!\n\n\n\n";

void main(void *mbd, uint32_t magic) {
  vga_init();
  vga_cls();
  for(int i=0; i<10;  i++)
       vga_puts(hello);



  while (1)
    ; // just spin
}
