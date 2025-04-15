#ifndef _COORDS_H
#define _COORDS_H

#include <linebot/coords.h>

void
coords_init(void);

int
coords_validate(linebot_coords_t const h_self);

void
coords_copy(linebot_coords_t const self, linebot_coords_t const other);

bool
coords_is_on_route(linebot_coords_t const self);

bool
coords_is_on_finish(linebot_coords_t const self);

void
coords_compute_mass_center(linebot_coords_t const self, int8_t *value);

#endif