#ifndef _DEVICES_TIMEOUT_GUARD_H
#define _DEVICES_TIMEOUT_GUARD_H

typedef enum
{
    DEVICE_TIMEOUT_GUARD_ROUTE
} device_timeout_guard_t;

#define DEVICE_TIMEOUT_GUARD_INSTANCES_NUM 1

int
device_timeout_guard_start(device_timeout_guard_t const h_self);

int
device_timeout_guard_stop(device_timeout_guard_t const h_self);

int
device_timeout_guard_read(device_timeout_guard_t const h_self);

#endif
