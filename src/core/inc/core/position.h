#ifndef _CORE_POSITION_H
#define _CORE_POSITION_H

#include <stdint.h>
#include <stdbool.h>

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
    uint8_t left_3;
    uint8_t left_2;
    uint8_t left_1;
    uint8_t right_1;
    uint8_t right_2;
    uint8_t right_3;
} core_position_t;

typedef enum
{
    CORE_POSITION_NO_LINE,
    CORE_POSITION_ON_LINE,
} core_position_status_t;

void
core_position_init(core_position_t *self);

core_position_status_t
core_position_get_status(core_position_t *self);

int16_t
core_position_compute_error(core_position_t *self);

uint8_t
core_position_get_by_place(core_position_t *self, core_position_place_t place);

void
core_position_set_by_place(core_position_t      *self,
                           core_position_place_t place,
                           uint8_t               position);

bool
core_position_equals(core_position_t *self, core_position_t *other);

#endif