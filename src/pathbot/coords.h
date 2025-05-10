#ifndef _PATHBOT_COORDS_H
#define _PATHBOT_COORDS_H

#include <pathbot.h>
#include <stdbool.h>
#include <stdint.h>

bool
coords_is_on_route(pathbot_coords_t const *p_self);

bool
coords_is_off_route(pathbot_coords_t const *p_self);

bool
coords_is_on_finish(pathbot_coords_t const *p_self);

int8_t
coords_compute_mass_center(pathbot_coords_t const *p_self);

#endif
