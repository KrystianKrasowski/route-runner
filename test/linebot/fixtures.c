#include "fixtures.h"
#include <assert.h>

linebot_t
fixtures_linebot_acquire(linebot_mode_t const mode)
{
    linebot_t        linebot;
    linebot_coords_t coords = fixtures_coords_acquire(COORDS_OFF_ROUTE);

    assert(linebot_new(mode, coords, 20, &linebot));

    return linebot;
}

linebot_coords_t
fixtures_coords_acquire(fixtures_coords_type_t const type)
{
    linebot_coords_t coords;

    switch (type)
    {
        case COORDS_ON_ROUTE:
            assert(linebot_new_coords(0, 0, 100, 100, 0, 0, &coords));
            break;
        case COORDS_ON_FINISH:
            assert(linebot_new_coords(5, 0, 0, 0, 0, 5, &coords));
            break;
        case COORDS_OFF_ROUTE:
        default:
            assert(linebot_new_coords(0, 0, 0, 0, 0, 0, &coords));
            break;
    }

    return coords;
}