#include "string.h"

void reverse(char *begin, char *end) {
  char tmp;
  while (begin < end) {
    tmp = *begin;
    *begin = *end;
    *end = tmp;
    begin++;
    end--;
  }
}

char *itoa(int32_t n, char *buf, uint8_t base) {
  if (base < 2 || base > 16) {
    *buf = '\0';
    return buf;
  }
  char *array = "0123456789ABCDEF";
  char *ret = buf;
  uint8_t isNegative = 0;
  if (n < 0) {
    n = -n;
    isNegative = 1;
  }

  if (n == 0)
    *buf++ = '0';

  while (n) {
    *buf++ = *(array + (n % base));
    n = n / base;
  }
  if (isNegative)
    *buf++ = '-';
  *buf = '\0';
  reverse(ret, buf - 1);
  return ret;
}

void *memset(void *dst, uint8_t c, size_t n) {
  uint8_t *pointer = dst;
  while (n--)
    *pointer++ = c;
  return dst;
}

void *memcpy(void *dst, void *src, size_t n) {
  uint8_t *pointer = dst;
  while (n--)
    *pointer++ = *(uint8_t *)src++;
  return dst;
}

size_t strlen(char *str) {
  const char *s;
  for (s = str; *s; s++)
    ;
  return (s - str);
}

int8_t strcmp(const char *str1, const char *str2) {
  while (*str1 && *str1 == *str2) {
    str1++;
    str2++;
  }
  return *str1 - *str2;
}

char *strcpy(char *dst, const char *src) {
  char *ret = dst;
  while (*dst++ = *src++)
    ;
  return ret;
}

char *strcat(char *dst, const char *src) {
  char *ret = dst;
  while (*dst)
    dst++;
  while (*dst++ = *src++)
    ;
  return ret;
}

char *strncpy(char *dst, const char *src, size_t n) {
  char *ret = dst;
  while (n-- && (*dst++ = *src++))
    ;
  if (n == 0)
    *dst = '\0';
  return ret;
}

int8_t strncmp(const char *str1, const char *str2, size_t n) {
  while (n-- && *str1 && *str1 == *str2) {
    str1++;
    str2++;
  }
  return *str1 - *str2;
}
