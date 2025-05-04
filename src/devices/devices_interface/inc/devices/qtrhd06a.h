#ifndef _DEVICE_QTRHD06A_H
#define _DEVICE_QTRHD06A_H

#include <stdint.h>

typedef enum
{
    DEVICE_QTRHD06A_1,
} device_qtrhd06a_t;

int
device_qtrhd06a_read(device_qtrhd06a_t const h_self, uint8_t values[]);

#endif
