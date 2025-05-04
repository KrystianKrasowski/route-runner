#include <utils/volatile_string.h>

void
memset_volatile(volatile void *s, int c, size_t n)
{
    volatile char *p = s;

    while (n-- > 0)
    {
        *p++ = c;
    }
}

void
memcpy_volatile(volatile void *dest, void const *src, size_t n)
{
    volatile char *d = dest;
    char const    *s = src;

    while (n-- > 0)
    {
        *d++ = *s++;
    }
}
