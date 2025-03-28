#include "core/position.h"
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
    self->handled = false;
}

core_coords_t
core_position_get_coords(core_position_t *self)
{
    return self->coords;
}

bool
core_position_is_handled(core_position_t *self)
{
    return self->handled;
}

bool
core_position_is_line_detected(core_position_t *self)
{
    return core_coords_get_status(&self->coords) == CORE_COORDS_STATUS_ON_LINE;
}

bool
core_position_is_line_lost(core_position_t *self)
{
    core_coords_status_t coords_status = core_coords_get_status(&self->coords);
    int16_t              errors_sum    = core_position_sum_errors(self);

    return coords_status == CORE_COORDS_STATUS_OFF_LINE && errors_sum == 0;
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
    self->handled = true;

    return error;
}

int16_t
core_position_sum_errors(core_position_t *self)
{
    return stack_sum(&self->errors);
}