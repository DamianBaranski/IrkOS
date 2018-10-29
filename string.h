#ifndef STRING_H
#define STRING_H
#include "types.h"

char *itoa(char *buf, int32_t n, uint8_t base);
void *memset(void *dst, uint8_t src, size_t n);
void *memcpy(void *dst, void *src, size_t n);
size_t strlen(char *str);
int8_t strcmp(const char *str1, const char *str2);
char *strcpy(char *dst, const char *src);
char *strcat(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t n);
int8_t strncmp(const char *src1, const char *src2, size_t n);

#endif
