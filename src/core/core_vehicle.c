#include "core/types.h"
#include "core/vehicle.h"
#include "core_vehicle_command_apply.h"
#include "core_vehicle_state_apply.h"
#include "core_vehicle_motion_apply.h"
#include <string.h>

static inline void
init_state(core_vehicle_t *self);

void
core_vehicle_init(core_vehicle_t *self)
{
    memset(self, 0, sizeof(*self));
    init_state(self);
    core_motion_init(&self->motion);
    core_position_init(&self->position);
}

core_vehicle_state_t
core_vehicle_get_state(core_vehicle_t *self)
{
    uint16_t state;
    stack_peek(&self->state, &state);

    return state;
}

void
core_vehicle_set_state(core_vehicle_t *self, core_vehicle_state_t state)
{
    stack_push_rolling(&self->state, (uint16_t)state);
}

bool
core_vehicle_is_state_changed(core_vehicle_t *self)
{
    uint16_t bottom;
    uint16_t top;

    stack_peek_bottom(&self->state, &bottom);
    stack_peek(&self->state, &top);

    return stack_get_length(&self->state) == 1 || bottom != top;
}

void
core_vehicle_set_command(core_vehicle_t *self, uint16_t command)
{
    self->command = command;
}

uint16_t
core_vehicle_get_command(core_vehicle_t *self)
{
    return self->command;
}

void
core_vehicle_set_line_position(core_vehicle_t *self, core_position_t position)
{
    self->position = position;
}

bool
core_vehicle_is_line_detected(core_vehicle_t *self)
{
    return core_position_get_status(&self->position) ==
           CORE_POSITION_STRIGHT_ON_LINE;
}

core_motion_direction_t
core_vehicle_get_motion_direction(core_vehicle_t *self)
{
    return core_motion_get_direction(&self->motion);
}

int8_t
core_vehicle_get_motion_correction(core_vehicle_t *self)
{
    return core_motion_get_correction(&self->motion);
}

bool
core_vehicle_is_moving_forward(core_vehicle_t *self)
{
    return core_vehicle_get_motion_direction(self) == CORE_MOTION_FORWARD;
}

bool
core_vehicle_is_moving_backward(core_vehicle_t *self)
{
    return core_vehicle_get_motion_direction(self) == CORE_MOTION_BACKWARD;
}

void
core_vehicle_update_command(core_vehicle_t *self, uint16_t command)
{
    core_vehicle_command_apply(self, command);
}

void
core_vehicle_update_state(core_vehicle_t *self)
{
    core_vehicle_state_apply(self);
}

core_vehicle_result_t
core_vehicle_update_motion(core_vehicle_t *self)
{
    return core_vehicle_motion_apply(self);
}

static inline void
init_state(core_vehicle_t *self)
{
    stack_t state;
    stack_init(&state, 2);
    stack_push(&state, CORE_VEHICLE_STATE_MANUAL);

    self->state = state;
}