#ifndef _LINEBOT_MOTION_FACTORY_H
#define _LINEBOT_MOTION_FACTORY_H

#include "motion.h"
#include <linebot.h>

static linebot_motion_direction_t
create_manual_direction(uint16_t const commands);

static int8_t
create_manual_correction(uint16_t const commands);

linebot_result_t
motion_create_by_commands(uint16_t const           commands,
                          linebot_motion_t * const handle);

linebot_result_t
motion_create_by_position(position_t const         position,
                          linebot_motion_t * const handle);

linebot_result_t
motion_create_standby(linebot_motion_t * const handle);

#endif