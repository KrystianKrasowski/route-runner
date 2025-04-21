#ifndef _DRIVERS_L293_H
#define _DRIVERS_L293_H

#include <stdint.h>

typedef enum
{
    L293_CHANNEL_12,
    L293_CHANNEL_34,
} l293_t;

int
l293_set_left(l293_t h_self);

int
l293_set_right(l293_t h_self);

int
l293_set_stop(l293_t h_self);

int
l293_enable(l293_t h_self);

int
l293_disable(l293_t h_self);

#endif