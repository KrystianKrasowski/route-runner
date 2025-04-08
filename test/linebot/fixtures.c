#include "fixtures.h"
#include <assert.h>

linebot_t
fixtures_linebot_acquire(linebot_mode_t const mode)
{
    linebot_t        linebot;
    linebot_coords_t coords = fixtures_coords_acquire_off_route();

    assert(linebot_new(mode, coords, 20, &linebot));

    return linebot;
}

linebot_coords_t
fixtures_coords_acquire_off_route(void)
{
    linebot_coords_t coords;

    assert(linebot_new_coords(0, 0, 0, 0, 0, 0, &coords));

    return coords;
}

linebot_coords_t
fixtures_coords_acquire_on_route(void)
{
    linebot_coords_t coords;

    assert(linebot_new_coords(0, 0, 100, 100, 0, 0, &coords));

    return coords;
}

linebot_coords_t
fixtures_coords_acquire_on_finish(void)
{
    linebot_coords_t coords;

    assert(linebot_new_coords(5, 0, 0, 0, 0, 5, &coords));

    return coords;
}