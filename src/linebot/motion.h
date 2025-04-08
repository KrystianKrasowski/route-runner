#ifndef _LINEBOT_MOTION_H
#define _LINEBOT_MOTION_H

#include "position.h"
#include <linebot.h>

void
motion_init(void);

bool
motion_new(linebot_motion_direction_t direction,
           int8_t                     correction,
           linebot_motion_t * const   handle);

void
motion_release(linebot_motion_t const self);

linebot_motion_direction_t
motion_get_direction(linebot_motion_t const self);

int8_t
motion_get_correction(linebot_motion_t const self);

#endif