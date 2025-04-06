#ifndef _CORE_COORDS_H
#define _CORE_COORDS_H

#include <stdbool.h>
#include <stdint.h>

#define CORE_COORDS_LINE_DETECTION_TRESHOLD 3
#define CORE_COORDS_SIZE                    6

typedef struct
{
    uint8_t coordinates[CORE_COORDS_SIZE];
} core_coords_t;

core_coords_t
core_coords(
    uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3);

void
core_coords_compute_mass_center(core_coords_t *self, int8_t *error);

bool
core_coords_equals(core_coords_t *self, core_coords_t *other);

bool
core_coords_is_on_route(core_coords_t *self);

bool
core_coords_is_on_finish(core_coords_t *self);

#endif