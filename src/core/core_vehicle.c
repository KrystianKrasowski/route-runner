#include "core/types.h"
#include "core/vehicle.h"
#include <string.h>

static inline void
init_state(core_vehicle_t *self);

static inline void
init_position(core_vehicle_t *self);

static inline void
set_motion_correction(core_vehicle_t *self, core_motion_t *motion);

static inline void
set_motion_direction(core_vehicle_t *self, core_motion_t *motion);

static inline bool
is_state(core_vehicle_t *self, core_vehicle_state_t state);

static inline bool
contains_command(uint16_t remote_control, core_remote_control_t command);

void
core_vehicle_init(core_vehicle_t *self)
{
    memset(self, 0, sizeof(*self));
    init_state(self);
    core_motion_init(&self->motion);
    init_position(self);
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

core_position_t
core_vehicle_get_line_position(core_vehicle_t *self)
{
    return self->position;
}

bool
core_vehicle_is_line_detected(core_vehicle_t *self)
{
    bool middle_on_line      = self->position.middle >= 100;
    bool left_on_background  = self->position.left <= 20;
    bool right_on_background = self->position.right <= 20;

    return middle_on_line && (left_on_background || right_on_background);
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
core_vehicle_is_movint_backward(core_vehicle_t *self)
{
    return core_vehicle_get_motion_direction(self) == CORE_MOTION_BACKWARD;
}

void
core_vehicle_apply_remote_control(core_vehicle_t *self, uint16_t command)
{
    if (is_state(self, CORE_VEHICLE_STATE_LINE_FOLLOWING) &&
        contains_command(command, CORE_REMOTE_CONTROL_BREAK))
    {
        core_vehicle_set_command(self, CORE_REMOTE_CONTROL_BREAK);
        return;
    }

    if (is_state(self, CORE_VEHICLE_STATE_LINE_FOLLOWING) &&
        !contains_command(command, CORE_REMOTE_CONTROL_BREAK))
    {
        core_vehicle_set_command(self, CORE_REMOTE_CONTROL_NONE);
        return;
    }

    if (is_state(self, CORE_VEHICLE_STATE_MANUAL) &&
        contains_command(command, CORE_REMOTE_CONTROL_FOLLOW))
    {
        core_vehicle_set_command(self, command - CORE_REMOTE_CONTROL_FOLLOW);
        return;
    }

    core_vehicle_set_command(self, command);
}

core_vehicle_result_t
core_vehicle_update_motion(core_vehicle_t *self)
{
    core_motion_t motion;
    core_motion_init(&motion);
    set_motion_correction(self, &motion);
    set_motion_direction(self, &motion);

    if (!core_motion_equals(&self->motion, &motion))
    {
        self->motion = motion;
        return CORE_VEHICLE_MOTION_CHANGED;
    }
    else
    {
        return CORE_VEHICLE_MOTION_REMAINS;
    }
}

static inline void
init_state(core_vehicle_t *self)
{
    stack_t state;
    stack_init(&state, 2);
    stack_push(&state, CORE_VEHICLE_STATE_MANUAL);

    self->state = state;
}

static inline void
init_position(core_vehicle_t *self)
{
    core_position_t position;
    memset(&position, 0, sizeof(position));
    self->position = position;
}

static inline void
set_motion_correction(core_vehicle_t *self, core_motion_t *motion)
{
    if (self->command & CORE_REMOTE_CONTROL_LEFT)
    {
        motion->correction = -90;
    }
    else if (self->command & CORE_REMOTE_CONTROL_RIGHT)
    {
        motion->correction = 90;
    }
    else
    {
        motion->correction = 0;
    }
}

static inline void
set_motion_direction(core_vehicle_t *self, core_motion_t *motion)
{
    if (self->command & CORE_REMOTE_CONTROL_FORWARD)
    {
        motion->direction = CORE_MOTION_FORWARD;
    }
    else if (self->command & CORE_REMOTE_CONTROL_BACKWARD)
    {
        motion->direction = CORE_MOTION_BACKWARD;
    }
    else
    {
        motion->direction  = CORE_MOTION_NONE;
        motion->correction = 0;
    }
}

static inline bool
is_state(core_vehicle_t *self, core_vehicle_state_t state)
{
    return core_vehicle_get_state(self) == state;
}

static inline bool
contains_command(uint16_t remote_control, core_remote_control_t command)
{
    return remote_control & command;
}