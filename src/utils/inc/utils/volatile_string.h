#ifndef _UTILS_VOLATILE_STRING_H
#define _UTILS_VOLATILE_STRING_H

#include <stddef.h>

void
memset_volatile(volatile void *s, int c, size_t n);

void
memcpy_volatile(volatile void *dest, volatile void const *src, size_t n);

#endif
