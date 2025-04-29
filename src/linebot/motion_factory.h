#ifndef _LINEBOT_MOTION_FACTORY_H
#define _LINEBOT_MOTION_FACTORY_H

#include "position.h"
#include <linebot/motion.h>

linebot_lgc_motion_t
motion_create_by_commands(uint16_t const commands);

linebot_lgc_motion_t
motion_create_by_position(position_t const h_position);

linebot_lgc_motion_t
motion_create_standby(void);

#endif
