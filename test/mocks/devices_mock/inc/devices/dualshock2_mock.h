#ifndef _DEVICE_DUALSHOCK2_MOCK_H
#define _DEVICE_DUALSHOCK2_MOCK_H

#include <devices/dualshock2.h>
#include <stdint.h>

void
device_dualshock2_mock_init(void);

void
device_dualshock2_mock_deinit(void);

void
device_dualshock2_mock_set_buttons(device_dualshock2_t const h_self,
                                   uint16_t const            buttons);

#endif
