#ifndef _MODE_H
#define _MODE_H

#include <linebot/command.h>
#include <linebot/coords.h>
#include <linebot/mode.h>
#include <stdint.h>

linebot_mode_t
mode_change_by_commands(linebot_mode_t const self, uint16_t const commands);

linebot_mode_t
mode_change_by_coords(linebot_mode_t const self, linebot_coords_t const coords);

#endif