#ifndef _DEVICES_BLINK_H
#define _DEVICES_BLINK_H

#include <stdint.h>

typedef enum
{
    DEVICE_BLINK_1,
} device_blink_t;

int
device_blink_set_toggles(device_blink_t const h_self, uint8_t num);

#endif
