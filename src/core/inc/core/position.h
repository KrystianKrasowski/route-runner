#ifndef _CORE_POSITION_H
#define _CORE_POSITION_H

#include "coords.h"
#include <stdbool.h>
#include <utils/stack.h>

typedef struct core_position
{
    core_coords_t coords;
    stack_t       errors;
} core_position_t;

core_position_t
core_position(core_coords_t coords, stack_t errors);

void
core_position_update_coords(core_position_t *self, core_coords_t coords);

bool
core_position_is_on_route(core_position_t *self);

bool
core_position_is_on_finish(core_position_t *self);

int8_t
core_position_last_error(core_position_t *self);

int8_t
core_position_update_error(core_position_t *self);

int16_t
core_position_sum_errors(core_position_t *self);

int8_t
core_position_regulate(core_position_t *self);

#endif