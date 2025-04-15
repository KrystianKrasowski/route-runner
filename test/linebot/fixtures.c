#include "fixtures.h"
#include <assert.h>

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
    int              result;
    linebot_coords_t coords;

    switch (type)
    {
        case COORDS_ON_ROUTE:
            result = linebot_coords_acquire(0, 0, 100, 100, 0, 0, &coords);
            break;
        case COORDS_ON_FINISH:
            result = linebot_coords_acquire(5, 0, 0, 0, 0, 5, &coords);
            break;
        case COORDS_OFF_ROUTE:
        default:
            result = linebot_coords_acquire(0, 0, 0, 0, 0, 0, &coords);
            break;
    }

    assert(result >= 0);

    return coords;
}