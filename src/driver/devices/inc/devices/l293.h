#ifndef _DEVICES_L293_H
#define _DEVICES_L293_H

#include <stdint.h>

typedef enum
{
    DEVICES_L293_CHANNEL_12,
    DEVICES_L293_CHANNEL_34,
} l293_t;

int
devices_l293_set_left(l293_t h_self);

int
devices_l293_set_right(l293_t h_self);

int
devices_l293_set_stop(l293_t h_self);

int
devices_l293_enable(l293_t h_self, uint8_t duty_cycle);

int
devices_l293_disable(l293_t h_self);

#endif