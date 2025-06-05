#ifndef _DEVICES_SERIAL_IN_H
#define _DEVICES_SERIAL_IN_H

#define DEVICE_SERIAL_IN_INSTANCES_NUM 1

typedef enum
{
    DEVICE_SERIAL_IN_1 = 0,
} device_serial_in_t;

int
device_serial_in_read(device_serial_in_t const h_self, char const command);

#endif
