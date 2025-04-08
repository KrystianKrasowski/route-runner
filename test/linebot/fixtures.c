#include "fixtures.h"

linebot_t
linebot_fixture_acquire(linebot_mode_t const mode)
{
    linebot_coords_t coords;
    linebot_t        linebot;

    linebot_new(mode, coords, 20, &linebot);

    return linebot;
}