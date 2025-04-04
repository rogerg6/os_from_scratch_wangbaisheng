#include "include/types.h"

void* memset(void *s, int8_t c, uint32_t n) {
    char *tmp = s;

    while (n--)
        *tmp++ = c;
    return s;
}

void memcpy(void *dest, const void *src, int n) {
    char *d = dest;
    const char *s = src;

    while (n--) {
        *d++ = *s++;
    }
}