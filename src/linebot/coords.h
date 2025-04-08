#ifndef _LINEBOT_COORDS_H
#define _LINEBOT_COORDS_H

#include <linebot.h>

void
coords_init(void);

bool
coords_new(uint8_t const            l3,
           uint8_t const            l2,
           uint8_t const            l1,
           uint8_t const            r1,
           uint8_t const            r2,
           uint8_t const            r3,
           linebot_coords_t * const handle);

void
coords_release(linebot_coords_t const self);

void
coords_copy(linebot_coords_t const self, linebot_coords_t const other);

bool
coords_is_on_route(linebot_coords_t const self);

bool
coords_is_on_finish(linebot_coords_t const self);

void
coords_compute_mass_center(linebot_coords_t const self, int8_t *value);

#endif