#ifndef _DEVICES_BLINK_MOCK_H
#define _DEVICES_BLINK_MOCK_H

#include <devices/blink.h>

void
device_blink_mock_init(void);

void
device_blink_mock_deinit(void);

uint8_t
device_blink_mock_verify_toggles_num(device_blink_t const h_self);

#endif
