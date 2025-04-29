#ifndef _DEVICES_L293_H
#define _DEVICES_L293_H

#include <stdint.h>

#define DEVICES_L293_INSTANCES_NUM 2

typedef enum
{
    DEVICES_L293_CHANNEL_12,
    DEVICES_L293_CHANNEL_34,
} device_l293_t;

int
devices_l293_set_left(device_l293_t h_self);

int
devices_l293_set_right(device_l293_t h_self);

int
devices_l293_set_stop(device_l293_t h_self);

int
devices_l293_enable(device_l293_t h_self, uint8_t duty_cycle);

int
devices_l293_disable(device_l293_t h_self);

#endif
