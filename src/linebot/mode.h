#ifndef _LINEBOT_MODE_H
#define _LINEBOT_MODE_H

#include <linebot.h>

bool
mode_is_manual(linebot_mode_t const self);

bool
mode_is_route_detected(linebot_mode_t const self);

bool
mode_is_tracking_route(linebot_mode_t const self);

bool
mode_is_following_route(linebot_mode_t const self);

bool
mode_is_recovering_route(linebot_t const self);

linebot_mode_t
mode_change_by_commands(linebot_mode_t const self, uint16_t const commands);

linebot_mode_t
mode_change_by_coords(linebot_mode_t const self, linebot_coords_t const coords);

#endif