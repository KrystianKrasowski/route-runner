#ifndef _ADAPTERS_MOTION_L293_H
#define _ADAPTERS_MOTION_L293_H

#include <devices/l293.h>
#include <linebot/port.h>
#include <stdint.h>

void
adapter_motion_l293_init(void);

int
adapter_motion_l293_acquire(device_l293_t const    h_motor_left,
                            device_l293_t const    h_motor_right,
                            linebot_port_motion_t *ph_self);

void
adapter_motion_l293_release(linebot_port_motion_t const h_self);

#endif
