#ifndef _DEVICES_SERIAL_H
#define _DEVICES_SERIAL_H

#define DEVICE_SERIAL_INSTANCES_NUM 1

typedef enum
{
    DEVICE_SERIAL_1 = 0,
} device_serial_t;

int
device_serial_read(device_serial_t const h_self, char const command);

#endif
