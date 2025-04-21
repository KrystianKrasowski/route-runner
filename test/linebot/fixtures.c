#include "fixtures.h"
#include <assert.h>
#include <string.h>

linebot_t
fixtures_linebot_acquire(linebot_mode_t const mode)
{
    linebot_t        linebot;
    linebot_coords_t coords = fixtures_coords_acquire(COORDS_OFF_ROUTE);

    assert(linebot_acquire(mode, coords, 20, &linebot) >= 0);

    return linebot;
}

linebot_coords_t
fixtures_coords_acquire(fixtures_coords_type_t const type)
{
    uint8_t          values[6];
    linebot_coords_t coords;

    memset(values, 0, sizeof(values));

    if (COORDS_ON_ROUTE == type)
    {
        values[2] = 100;
        values[3] = 100;
    }
    else if (COORDS_ON_FINISH == type)
    {
        values[0] = 5;
        values[5] = 5;
    }

    assert(linebot_coords_acquire(values, 6, &coords) >= 0);

    return coords;
}