#include "core/position.h"
#include "core_position_regulator.h"
#include <string.h>

void
core_position_init(core_position_t *self)
{
    memset(self, 0, sizeof(*self));
    stack_t errors;
    stack_init(&errors, 20);
    self->errors = errors;
}

void
core_position_update_coords(core_position_t *self, core_coords_t coords)
{
    self->coords = coords;
}

bool
core_position_is_on_route(core_position_t *self)
{
    return core_coords_get_status(&self->coords) == CORE_COORDS_STATUS_ON_ROUTE;
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