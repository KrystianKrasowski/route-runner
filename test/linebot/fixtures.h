#ifndef _LINEBOT_FIXTURES_H
#define _LINEBOT_FIXTURES_H

#include <linebot/api.h>

typedef enum
{
    COORDS_ON_ROUTE,
    COORDS_OFF_ROUTE,
    COORDS_ON_FINISH,
} fixtures_coords_type_t;

linebot_t
fixtures_linebot_acquire(linebot_mode_t const mode);

linebot_coords_t
fixtures_coords_acquire(fixtures_coords_type_t const type);

#endif