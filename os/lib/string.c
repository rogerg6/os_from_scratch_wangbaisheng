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

int strcmp(const char *s1, const char *s2) {
    unsigned char c1, c2;

    while (1) {
        c1 = *s1++;
        c2 = *s2++;
        if (c1 != c2)
            return c1 < c2 ? -1 : 1;
        if (!c1)
            break;
    }
    return 0;
}

int strlen(const char *s) {
    const char *c;
    for (c = s; *c != '\0'; c++);
    return c - s;
}