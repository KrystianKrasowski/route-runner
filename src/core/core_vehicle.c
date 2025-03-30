#include "core/types.h"
#include "core/vehicle.h"
#include <string.h>

#define KP 0.6
#define KI 0
#define KD 3.2

static inline void
mode_transit_from_line_detected(core_vehicle_t *self);

static inline void
mode_transit_from_line_following(core_vehicle_t *self);

static inline void
mode_transit_from_manual(core_vehicle_t *self);

static inline core_vehicle_result_t
motion_create_tracking(core_vehicle_t *self, core_motion_t *result);

static inline core_vehicle_result_t
motion_create_manual(core_vehicle_t *self, core_motion_t *result);

static inline int8_t
pid_regulation(core_position_t *position);

void
core_vehicle_init(core_vehicle_t *self)
{
    memset(self, 0, sizeof(*self));
    core_motion_init(&self->motion);
    core_position_init(&self->position);
    core_mode_init(&self->mode);
}

core_mode_value_t
core_vehicle_get_mode_value(core_vehicle_t *self)
{
    return core_mode_get(&self->mode);
}

void
core_vehicle_set_mode_value(core_vehicle_t *self, core_mode_value_t value)
{
    core_mode_set(&self->mode, value);
}

bool
core_vehicle_is_mode_changed(core_vehicle_t *self)
{
    return core_mode_changed(&self->mode);
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
core_vehicle_create_motion(core_vehicle_t *self, core_motion_t *result)
{
    switch (core_vehicle_get_mode_value(self))
    {
        case CORE_MODE_LINE_FOLLOWING:
            return motion_create_tracking(self, result);
        default:
            return motion_create_manual(self, result);
    }
}

static inline void
mode_transit_from_line_detected(core_vehicle_t *self)
{
    if (!core_position_is_line_detected(&self->position))
    {
        core_mode_set(&self->mode, CORE_MODE_MANUAL);
    }
    else if (core_vehicle_is_commanded(self, CORE_REMOTE_CONTROL_FOLLOW))
    {
        core_mode_set(&self->mode, CORE_MODE_LINE_FOLLOWING);
    }
    else
    {
        core_mode_set(&self->mode, CORE_MODE_LINE_DETECTED);
    }
}

static inline void
mode_transit_from_line_following(core_vehicle_t *self)
{
    if (core_vehicle_is_commanded(self, CORE_REMOTE_CONTROL_BREAK))
    {
        core_mode_set(&self->mode, CORE_MODE_MANUAL);
    }
    else if (core_position_is_line_lost(&self->position))
    {
        core_mode_set(&self->mode, CORE_MODE_MANUAL);
        core_vehicle_update_command(self, CORE_REMOTE_CONTROL_NONE);
    }
    else
    {
        core_mode_set(&self->mode, CORE_MODE_LINE_FOLLOWING);
    }
}

static inline void
mode_transit_from_manual(core_vehicle_t *self)
{
    if (core_position_is_line_detected(&self->position))
    {
        core_mode_set(&self->mode, CORE_MODE_LINE_DETECTED);
    }
    else
    {
        core_mode_set(&self->mode, CORE_MODE_MANUAL);
    }
}

static inline core_vehicle_result_t
motion_create_tracking(core_vehicle_t *self, core_motion_t *result)
{
    if (!core_position_is_handled(&self->position))
    {
        core_motion_set_correction(result, pid_regulation(&self->position));
        core_motion_set_direction(result, CORE_MOTION_FORWARD);

        self->motion = *result;

        return CORE_VEHICLE_MOTION_CHANGED;
    }
    else
    {
        return CORE_VEHICLE_MOTION_REMAINS;
    }
}

static inline core_vehicle_result_t
motion_create_manual(core_vehicle_t *self, core_motion_t *result)
{
    if (core_vehicle_is_commanded(self, CORE_REMOTE_CONTROL_LEFT))
    {
        core_motion_set_correction(result, -50);
    }
    else if (core_vehicle_is_commanded(self, CORE_REMOTE_CONTROL_RIGHT))
    {
        core_motion_set_correction(result, 50);
    }
    else
    {
        core_motion_set_correction(result, 0);
    }

    if (core_vehicle_is_commanded(self, CORE_MOTION_FORWARD))
    {
        core_motion_set_direction(result, CORE_MOTION_FORWARD);
    }
    else if (core_vehicle_is_commanded(self, CORE_MOTION_BACKWARD))
    {
        core_motion_set_direction(result, CORE_MOTION_BACKWARD);
    }
    else
    {
        core_motion_set_direction(result, CORE_MOTION_NONE);
        core_motion_set_correction(result, 0);
    }

    if (core_motion_equals(&self->motion, result))
    {
        return CORE_VEHICLE_MOTION_REMAINS;
    }
    else
    {
        self->motion = *result;
        return CORE_VEHICLE_MOTION_CHANGED;
    }
}

static inline int8_t
pid_regulation(core_position_t *position)
{
    int8_t  previous   = core_position_last_error(position);
    int8_t  error      = core_position_update_error(position);
    int16_t all_errors = core_position_sum_errors(position);

    int16_t correction = KP * error + KI * all_errors + KD * (error - previous);

    if (correction > 100)
    {
        return 100;
    }
    else if (correction < -100)
    {
        return -100;
    }
    else
    {
        return correction;
    }
}