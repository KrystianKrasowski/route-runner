#ifndef _PATHBOT_FIXTURES_H
#define _PATHBOT_FIXTURES_H

#include <pathbot.h>

extern pathbot_coords_t const FIXTURES_COORDS6_ON_ROUTE;
extern pathbot_coords_t const FIXTURES_COORDS6_OFF_ROUTE;
extern pathbot_coords_t const FIXTURES_COORDS6_ON_FINISH;

pathbot_coords_t
fixtures_coords6_of(
    uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3);

#endif
