#include "core/position.h"
#include "core_position_regulator.h"
#include <string.h>

core_position_t
core_position(core_coords_t coords, stack_t errors)
{
    core_position_t position;
    position.coords = coords;
    position.errors = errors;

    return position;
}

void
core_position_update_coords(core_position_t *self, core_coords_t coords)
{
    self->coords = coords;
}

bool
core_position_is_on_route(core_position_t *self)
{
    return core_coords_is_on_route(&self->coords);
}

bool
core_position_is_on_finish(core_position_t *self)
{
    return core_coords_is_on_finish(&self->coords);
}

int8_t
core_position_last_error(core_position_t *self)
{
    int16_t error = 0;
    stack_peek(&self->errors, &error);

    return (int8_t)error;
}

int8_t
core_position_update_error(core_position_t *self)
{
    int8_t error = core_position_last_error(self);
    core_coords_compute_mass_center(&self->coords, &error);
    stack_push_rolling(&self->errors, error);

    return error;
}

int16_t
core_position_sum_errors(core_position_t *self)
{
    return stack_sum(&self->errors);
}

int8_t
core_position_regulate(core_position_t *self)
{
    return core_position_regulate_pid(self);
}