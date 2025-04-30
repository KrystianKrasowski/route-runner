#ifndef _DEVICES_MOCK_L293_H
#define _DEVICES_MOCK_L293_H

#include <devices/l293.h>
#include <stdbool.h>

void
devices_l293_mock_init(void);

void
devices_l293_mock_deinit(void);

device_l293_rotation_t
devices_l293_mock_verify_rotation(device_l293_t const h_self);

bool
devices_l293_mock_is_enabled(device_l293_t const h_self);

uint8_t
devices_l293_mock_verify_duty_cycle(device_l293_t const h_self);

#endif
