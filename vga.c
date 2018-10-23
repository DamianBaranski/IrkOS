#include "vga.h"
#include "memory.h"
#include "types.h"

#define SCREEN_WIDTH 80 
#define SCREEN_HEIGHT 25
#define VGA_RAM_COLOR (uint16_t*)0xB8000

struct {
  uint16_t *mem;
  uint8_t x;
  uint8_t y;
} vga;

void vga_init() {
	vga.mem = VGA_RAM_COLOR;
	vga.x = 0;
	vga.y = 0;
}
void vga_cls() {
	memset(vga.mem, 0, sizeof(vga.mem)*SCREEN_WIDTH*SCREEN_HEIGHT);
}

void vga_puts(const char *string){
	char *buff;
       buff = string;
	while(*buff != 0) {
		switch(*buff) {
			case '\n':
				vga.x = 0;
				vga.y++;
				break;
			case '\r':
				vga.x = 0;
				break;
			case '\t':
				vga.x += 5;
			       break;
			default:	       
				*(vga.mem + vga.x + vga.y*SCREEN_WIDTH) = *buff | 0x0F00;
				vga.x++;
		}
		if(vga.x > SCREEN_WIDTH) {
			vga.x = 0;
			vga.y++;
		}
		if(vga.y > SCREEN_HEIGHT)
		{
			//scroll one line;
			vga.y--;
		}
		buff++;
		
	}
}

