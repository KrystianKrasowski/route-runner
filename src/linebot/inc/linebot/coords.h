#ifndef _LINEBOT_COORDS_H
#define _LINEBOT_COORDS_H

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t linebot_coords_t;

bool
linebot_new_coords(uint8_t const            l3,
                   uint8_t const            l2,
                   uint8_t const            l1,
                   uint8_t const            r1,
                   uint8_t const            r2,
                   uint8_t const            r3,
                   linebot_coords_t * const handle);

void
linebot_free_coords(linebot_coords_t const coords);

#endif