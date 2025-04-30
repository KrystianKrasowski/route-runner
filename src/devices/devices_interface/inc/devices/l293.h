#ifndef _DEVICES_L293_H
#define _DEVICES_L293_H

#include <stdint.h>

#define DEVICES_L293_INSTANCES_NUM 2

typedef enum
{
    DEVICES_L293_CHANNEL_12,
    DEVICES_L293_CHANNEL_34,
} device_l293_t;

typedef enum
{
    DEVICES_L293_ROTATION_LEFT,
    DEVICES_L293_ROTATION_RIGHT,
    DEVICES_L293_ROTATION_STOP,
} device_l293_rotation_t;

int
devices_l293_rotate(device_l293_t h_self, device_l293_rotation_t rotation);

int
devices_l293_enable(device_l293_t h_self, uint8_t duty_cycle);

int
devices_l293_disable(device_l293_t h_self);

#endif
