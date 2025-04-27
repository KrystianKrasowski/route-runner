#ifndef _ADAPTERS_MOTION_L293_H
#define _ADAPTERS_MOTION_L293_H

#include <devices/l293.h>
#include <linebot/port.h>

void
adapters_motion_l293_init(void);

int
adapters_motion_l293_acquire(l293_t const           h_motor_left,
                             l293_t const           h_motor_right,
                             linebot_port_motion_t *ph_self);

#endif
