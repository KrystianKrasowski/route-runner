#ifndef _DEVICES_SERIAL_H
#define _DEVICES_SERIAL_H

#include <stdint.h>

#define DEVICE_SERIAL_INSTANCES_NUM   1
#define DEVICE_SERIAL_MAX_LINE_LENGTH 80

typedef enum
{
    DEVICE_SERIAL_1 = 0,
} device_serial_t;

int
device_serial_read(device_serial_t const h_self, char const command);

int
device_serial_send(device_serial_t const h_self,
                   char const            message[],
                   uint8_t               length);

#endif
