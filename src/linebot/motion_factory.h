#ifndef _LINEBOT_MOTION_FACTORY_H
#define _LINEBOT_MOTION_FACTORY_H

#include "position.h"
#include <linebot/motion.h>

bool
motion_create_by_commands(uint16_t const           commands,
                          linebot_motion_t * const handle);

bool
motion_create_by_position(position_t const         position,
                          linebot_motion_t * const handle);

bool
motion_create_standby(linebot_motion_t * const handle);

#endif