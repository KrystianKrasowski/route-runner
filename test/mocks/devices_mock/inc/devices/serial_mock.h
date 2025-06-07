#ifndef _DEVICES_SERIAL_IN_MOCK_H_H
#define _DEVICES_SERIAL_IN_MOCK_H_H

#include <devices/serial.h>

void
device_serial_mock_init(void);

void
device_serial_mock_deinit(void);

void
device_serial_mock_set_requested(device_serial_t const h_device,
                                 char const            command);

char *
device_serial_mock_get_applied_msg(device_serial_t const h_device);

#endif
