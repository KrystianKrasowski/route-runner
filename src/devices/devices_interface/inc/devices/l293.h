#ifndef _DEVICE_L293_H
#define _DEVICE_L293_H

#include <stdint.h>

#define DEVICE_L293_INSTANCES_NUM 2

typedef enum
{
    DEVICE_L293_CHANNEL_12,
    DEVICE_L293_CHANNEL_34,
} device_l293_t;

typedef enum
{
    DEVICE_L293_ROTATION_LEFT,
    DEVICE_L293_ROTATION_RIGHT,
    DEVICE_L293_ROTATION_STOP,
} device_l293_rotation_t;

int
device_l293_rotate(device_l293_t const          h_self,
                   device_l293_rotation_t const rotation);

int
device_l293_enable(device_l293_t const h_self, uint8_t duty_cycle);

int
device_l293_disable(device_l293_t const h_self);

#endif
