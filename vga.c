#include "vga.h"
#include "string.h"
#include "types.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define VGA_RAM_COLOR (uint16_t *)0xB8000

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
  memset(vga.mem, 0, sizeof(vga.mem) * SCREEN_WIDTH * SCREEN_HEIGHT);
}

void vga_put(char ch) {
  switch (ch) {
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
    *(vga.mem + vga.x + vga.y * SCREEN_WIDTH) = ch | 0x0F00;
    vga.x++;
  }
  if (vga.x > SCREEN_WIDTH) {
    vga.x = 0;
    vga.y++;
  }
  if (vga.y > SCREEN_HEIGHT) {
    // scroll one line;
    vga.y--;
  }
}

void vga_puts(const char *string) {
  while (*string) {
    vga_put(*string);
    string++;
  }
}

void kprintf(char const *fmt, ...) {
  va_list arg;
  va_start(arg, fmt);
  char ch;
  char char_temp;
  char *string_temp;
  int int_temp;
  char buffer[33];
  while (ch = *fmt++) {
    if ('%' == ch) {
      switch (ch = *fmt++) {
      /* %% - print out a single %    */
      case '%':
        vga_put('%');
        break;

      /* %c: print out a character    */
      case 'c':
        char_temp = va_arg(arg, int);
        vga_put(char_temp);
        break;

      /* %s: print out a string       */
      case 's':
        string_temp = va_arg(arg, char *);
        vga_puts(string_temp);
        break;

      /* %d: print out an int         */
      case 'd':
        int_temp = va_arg(arg, int);
        itoa(int_temp, buffer, 10);
        vga_puts(buffer);
        break;

      /* %x: print out an int in hex  */
      case 'x':
        int_temp = va_arg(arg, int);
        itoa(int_temp, buffer, 16);
        vga_puts(buffer);
        break;
      }
    } else {
      vga_put(ch);
    }
  }
}
