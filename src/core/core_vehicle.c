#include "core/types.h"
#include "core/vehicle.h"
#include "core_vehicle_manual_motion_apply.h"
#include "core_vehicle_tracking_motion_apply.h"
#include <string.h>

static inline void
init_mode(core_vehicle_t *self);

static inline void
mode_transit_from_line_detected(core_vehicle_t *self);

static inline void
mode_transit_from_line_following(core_vehicle_t *self);

static inline void
mode_transit_from_manual(core_vehicle_t *self);

void
core_vehicle_init(core_vehicle_t *self)
{
    memset(self, 0, sizeof(*self));
    init_mode(self);
    core_motion_init(&self->motion);
    core_position_init(&self->position);
}

core_mode_value_t
core_vehicle_get_mode_value(core_vehicle_t *self)
{
    int16_t value;
    stack_peek(&self->mode, &value);

    return value;
}

void
core_vehicle_set_mode_value(core_vehicle_t *self, core_mode_value_t value)
{
    stack_push_rolling(&self->mode, (int16_t)value);
}

bool
core_vehicle_is_mode_changed(core_vehicle_t *self)
{
    int16_t bottom;
    int16_t top;

    stack_peek_bottom(&self->mode, &bottom);
    stack_peek(&self->mode, &top);

    return stack_get_length(&self->mode) == 1 || bottom != top;
}

uint16_t
core_vehicle_get_command(core_vehicle_t *self)
{
    return self->command;
}

bool
core_vehicle_is_commanded(core_vehicle_t *self, uint16_t command)
{
    return self->command & command;
}

void
core_vehicle_update_coords(core_vehicle_t *self, core_coords_t coords)
{
    core_position_update_coords(&self->position, coords);
}

// TODO: Delete
core_coords_t
core_vehicle_get_coords(core_vehicle_t *self)
{
    return core_position_get_coords(&self->position);
}

int8_t
core_vehicle_last_position_error(core_vehicle_t *self)
{
    return core_position_last_error(&self->position);
}

int16_t
core_vehicle_get_position_errors_sum(core_vehicle_t *self)
{
    return core_position_sum_errors(&self->position);
}

bool
core_vehicle_is_position_updated(core_vehicle_t *self)
{
    return core_position_is_handled(&self->position);
}

void
core_vehicle_set_motion(core_vehicle_t *self, core_motion_t motion)
{
    self->motion = motion;
}

bool
core_vehicle_motion_differs(core_vehicle_t *self, core_motion_t *motion)
{
    return !core_motion_equals(&self->motion, motion);
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

void
core_vehicle_set_motion_direction(core_vehicle_t         *self,
                                  core_motion_direction_t direction)
{
    core_motion_set_direction(&self->motion, direction);
}

void
core_vehicle_set_motion_correction(core_vehicle_t *self, int8_t correction)
{
    core_motion_set_correction(&self->motion, correction);
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
    core_mode_value_t mode               = core_vehicle_get_mode_value(self);
    bool              is_mode_follow     = mode == CORE_MODE_LINE_FOLLOWING;
    bool              is_mode_manual     = mode == CORE_MODE_MANUAL;
    bool              has_command_break  = command & CORE_REMOTE_CONTROL_BREAK;
    bool              has_command_follow = command & CORE_REMOTE_CONTROL_FOLLOW;

    if (is_mode_follow && has_command_break)
    {
        self->command = CORE_REMOTE_CONTROL_BREAK;
    }
    else if (is_mode_follow && !has_command_break)
    {
        self->command = CORE_REMOTE_CONTROL_NONE;
    }
    else if (is_mode_manual && has_command_follow)
    {
        self->command = command - CORE_REMOTE_CONTROL_FOLLOW;
    }
    else
    {
        self->command = command;
    }
}

void
core_vehicle_update_mode(core_vehicle_t *self)
{
    core_mode_value_t mode = core_vehicle_get_mode_value(self);

    switch (mode)
    {
        case CORE_MODE_LINE_DETECTED:
            mode_transit_from_line_detected(self);
            break;
        case CORE_MODE_LINE_FOLLOWING:
            mode_transit_from_line_following(self);
            break;
        case CORE_MODE_MANUAL:
        default:
            mode_transit_from_manual(self);
    }
}

core_vehicle_result_t
core_vehicle_update_motion(core_vehicle_t *self)
{
    switch (core_vehicle_get_mode_value(self))
    {
        case CORE_MODE_LINE_FOLLOWING:
            return core_vehicle_tracking_motion_apply(self);
        default:
            return core_vehicle_manual_motion_apply(self);
    }
}

int8_t
core_vehicle_update_position_error(core_vehicle_t *self)
{
    return core_position_update_error(&self->position);
}

static inline void
init_mode(core_vehicle_t *self)
{
    stack_t mode;
    stack_init(&mode, 2);
    stack_push(&mode, CORE_MODE_MANUAL);

    self->mode = mode;
}

static inline void
mode_transit_from_line_detected(core_vehicle_t *self)
{
    if (!core_position_is_line_detected(&self->position))
    {
        stack_push_rolling(&self->mode, CORE_MODE_MANUAL);
    }
    else if (core_vehicle_is_commanded(self, CORE_REMOTE_CONTROL_FOLLOW))
    {
        stack_push_rolling(&self->mode, CORE_MODE_LINE_FOLLOWING);
    }
    else
    {
        stack_push_rolling(&self->mode, CORE_MODE_LINE_DETECTED);
    }
}

static inline void
mode_transit_from_line_following(core_vehicle_t *self)
{
    if (core_vehicle_is_commanded(self, CORE_REMOTE_CONTROL_BREAK))
    {
        stack_push_rolling(&self->mode, CORE_MODE_MANUAL);
    }
    else if (core_position_is_line_lost(&self->position))
    {
        stack_push_rolling(&self->mode, CORE_MODE_MANUAL);
        core_vehicle_update_command(self, CORE_REMOTE_CONTROL_NONE);
    }
    else
    {
        stack_push_rolling(&self->mode, CORE_MODE_LINE_FOLLOWING);
    }
}

static inline void
mode_transit_from_manual(core_vehicle_t *self)
{
    if (core_position_is_line_detected(&self->position))
    {
        stack_push_rolling(&self->mode, CORE_MODE_LINE_DETECTED);
    }
    else
    {
        stack_push_rolling(&self->mode, CORE_MODE_MANUAL);
    }
}