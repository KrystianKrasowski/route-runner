#ifndef _DEVICE_QTRHD06A_H
#define _DEVICE_QTRHD06A_H

#include <stdint.h>

typedef enum
{
    DEVICE_QTRHD06A_1,
} device_qtrhd06a_t;

#define DEVICE_QTRHD06A_INSTANCES_NUM 1
#define DEVICE_QTRHD06A_VALUES_LENGTH 6

int
device_qtrhd06a_read(device_qtrhd06a_t const h_self, uint8_t values[]);

#endif
