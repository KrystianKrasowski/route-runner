#ifndef _LINEBOT_FIXTURES_H
#define _LINEBOT_FIXTURES_H

#include <linebot/api.h>

linebot_t
fixtures_linebot_acquire(linebot_mode_t const mode);

linebot_coords_t
fixtures_coords_acquire_off_route(void);

linebot_coords_t
fixtures_coords_acquire_on_route(void);

linebot_coords_t
fixtures_coords_acquire_on_finish(void);

#endif