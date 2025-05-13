#ifndef _PATHBOT_FIXTURES_H
#define _PATHBOT_FIXTURES_H

#include <pathbot/domain.h>

extern pathbot_coords_t const FIXTURES_COORDS6_ON_ROUTE;
extern pathbot_coords_t const FIXTURES_COORDS6_OFF_ROUTE;
extern pathbot_coords_t const FIXTURES_COORDS6_ON_FINISH;

extern pathbot_motion_t const FIXTURES_MOTION_NONE;

pathbot_coords_t
fixtures_coords6_of(
    uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3);

pathbot_motion_t
fixtures_motion_forward(int8_t correction);

pathbot_motion_t
fixtures_motion_backward(int8_t correction);

#endif
