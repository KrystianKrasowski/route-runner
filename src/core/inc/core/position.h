#ifndef _CORE_POSITION_H
#define _CORE_POSITION_H

#include <stdbool.h>
#include <stdint.h>

#define CORE_POSITION_DETECTION_TRESHOLD 3
#define CORE_POSITION_COORDS_SIZE        6

typedef enum
{
    CORE_POSITION_PLACE_LEFT_3,
    CORE_POSITION_PLACE_LEFT_2,
    CORE_POSITION_PLACE_LEFT_1,
    CORE_POSITION_PLACE_RIGHT_1,
    CORE_POSITION_PLACE_RIGHT_2,
    CORE_POSITION_PLACE_RIGHT_3
} core_position_place_t;

typedef struct
{
    uint8_t coordinates[CORE_POSITION_COORDS_SIZE];
} core_position_t;

typedef enum
{
    CORE_POSITION_ON_LINE,
    CORE_POSITION_OFF_LINE,
} core_position_status_t;

void
core_position_init(core_position_t *self);

core_position_status_t
core_position_get_status(core_position_t *self);

core_position_status_t
core_position_compute_error(core_position_t *self, int8_t *error);

uint8_t
core_position_get_by_place(core_position_t *self, core_position_place_t place);

void
core_position_set_by_place(core_position_t      *self,
                           core_position_place_t place,
                           uint8_t               position);

bool
core_position_equals(core_position_t *self, core_position_t *other);

#endif