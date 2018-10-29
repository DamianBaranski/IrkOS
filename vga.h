#ifndef VGA_H
#define VGA_H
#include <stdarg.h>
void vga_init();
void vga_cls();
void vga_puts(const char *string);
void kprintf(const char *fmt, ...);
#endif
