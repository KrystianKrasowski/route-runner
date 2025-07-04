#ifndef _DEVICES_BLINK_H
#define _DEVICES_BLINK_H

#include <stdint.h>

typedef enum
{
    DEVICE_BLINK_1,
} device_blink_t;

#define DEVICE_BLINK_INSTANCES_NUM 1

int
device_blink_set_sequence(device_blink_t const h_self, uint8_t seq);

#endif
