#ifndef _CORE_COORDS_H
#define _CORE_COORDS_H

#include <stdbool.h>
#include <stdint.h>

#define CORE_COORDS_LINE_DETECTION_TRESHOLD 3
#define CORE_COORDS_SIZE                    6

typedef enum
{
    CORE_COORDS_PLACE_LEFT_3,
    CORE_COORDS_PLACE_LEFT_2,
    CORE_COORDS_PLACE_LEFT_1,
    CORE_COORDS_PLACE_RIGHT_1,
    CORE_COORDS_PLACE_RIGHT_2,
    CORE_COORDS_PLACE_RIGHT_3
} core_coords_place_t;

typedef struct
{
    uint8_t coordinates[CORE_COORDS_SIZE];
} core_coords_t;

typedef enum
{
    CORE_COORDS_STATUS_ON_ROUTE,
    CORE_COORDS_STATUS_OFF_LINE,
} core_coords_status_t;

core_coords_t
core_coords(
    uint8_t l3, uint8_t l2, uint8_t l1, uint8_t r1, uint8_t r2, uint8_t r3);

core_coords_status_t
core_coords_get_status(core_coords_t *self);

core_coords_status_t
core_coords_compute_mass_center(core_coords_t *self, int8_t *error);

bool
core_coords_equals(core_coords_t *self, core_coords_t *other);

bool
core_coords_are_on_route(core_coords_t *self);

#endif