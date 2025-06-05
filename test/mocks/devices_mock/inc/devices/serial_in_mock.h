#ifndef _DEVICES_SERIAL_IN_MOCK_H_H
#define _DEVICES_SERIAL_IN_MOCK_H_H

#include <devices/serial_in.h>

void
device_serial_in_mock_init(void);

void
device_serial_in_mock_deinit(void);

void
device_serial_in_mock_set_requested(device_serial_in_t const h_device,
                                    char const               command);

#endif
