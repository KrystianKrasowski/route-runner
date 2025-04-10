#ifndef _LINEBOT_H
#define _LINEBOT_H

#include "position.h"
#include <linebot/api.h>

position_t
linebot_get_position(linebot_t const self);

bool
linebot_update_mode(linebot_t const self, linebot_mode_t mode);

bool
linebot_is_tracking_route(linebot_t const self);

#endif