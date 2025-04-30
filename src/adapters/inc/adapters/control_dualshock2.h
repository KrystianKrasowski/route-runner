#ifndef _ADAPTER_CONTROL_DUALSHOCK2_H
#define _ADAPTER_CONTROL_DUALSHOCK2_H

#include <devices/dualshock2.h>
#include <stdint.h>

int
adapter_control_dualshock2_read(device_dualshock2_t const h_dualshock,
                                uint16_t                 *p_commands);

#endif
