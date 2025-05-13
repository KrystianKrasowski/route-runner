#include "fixtures.h"

pathbot_coords_t const FIXTURES_COORDS6_ON_ROUTE = {
    .coords  = {0, 0, 100, 100, 0, 0},
    .weights = PATHBOT_COORDS6_WEIGHTS,
    .length  = 6,
};

pathbot_coords_t const FIXTURES_COORDS6_OFF_ROUTE = {
    .coords  = {0, 0, 0, 0, 0, 0},
    .weights = PATHBOT_COORDS6_WEIGHTS,
    .length  = 6,
};

pathbot_coords_t const FIXTURES_COORDS6_ON_FINISH = {
    .coords  = {5, 0, 0, 0, 0, 5},
    .weights = PATHBOT_COORDS6_WEIGHTS,
    .length  = 6,
};

pathbot_motion_t const FIXTURES_MOTION_NONE = {
    .direction  = PATHBOT_DIRECTION_NONE,
    .correction = 0,
};

pathbot_coords_t
fixtures_coords6_of(
    uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3)
{
    pathbot_coords_t coords = {
        .coords  = {l3, l2, l1, r1, r2, r3},
        .weights = PATHBOT_COORDS6_WEIGHTS,
        .length  = 6,
    };

    return coords;
}

pathbot_motion_t
fixtures_motion_forward(int8_t correction)
{
    pathbot_motion_t motion = {
        .direction  = PATHBOT_DIRECTION_FORWARD,
        .correction = correction,
    };

    return motion;
}

pathbot_motion_t
fixtures_motion_backward(int8_t correction)
{
    pathbot_motion_t motion = {
        .direction  = PATHBOT_DIRECTION_BACKWARD,
        .correction = correction,
    };

    return motion;
}
