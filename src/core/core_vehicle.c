#include "core/ports.h"
#include "core/vehicle.h"
#include "core_motion_factory.h"
#include <string.h>

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
    core_motion_init(&self->motion);
    core_position_init(&self->position);
    core_mode_init(&self->mode);

    self->control           = core_control_create(CORE_CONTROL_NONE);
    self->position_handeled = true;
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
core_vehicle_get_commands(core_vehicle_t *self)
{
    return core_control_get_commands(&self->control);
}

bool
core_vehicle_has_command(core_vehicle_t *self, core_control_command_t command)
{
    return core_control_has(&self->control, command);
}

int8_t
core_vehicle_position_regulate(core_vehicle_t *self)
{
    return core_position_regulate(&self->position);
}

void
core_vehicle_update_coords(core_vehicle_t *self, core_coords_t coords)
{
    core_position_update_coords(&self->position, coords);
    self->position_handeled = false;
}

void
core_vehicle_update_control(core_vehicle_t *self, core_control_t control)
{
    bool mode_follow   = core_mode_is(&self->mode, CORE_MODE_LINE_FOLLOWING);
    bool mode_manual   = core_mode_is(&self->mode, CORE_MODE_MANUAL);
    bool command_break = core_control_has(&control, CORE_CONTROL_BREAK);

    if (mode_follow && command_break)
    {
        core_control_set_commands(&self->control, CORE_CONTROL_BREAK);
    }
    else if (mode_follow && !command_break)
    {
        core_control_set_commands(&self->control, CORE_CONTROL_NONE);
    }
    else if (mode_manual)
    {
        uint16_t truncate_commands = CORE_CONTROL_BREAK | CORE_CONTROL_FOLLOW;
        core_control_truncate(&control, truncate_commands);

        self->control = control;
    }
    else
    {
        self->control = control;
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

void
core_vehicle_update_route_guard(core_vehicle_t *self)
{
    bool mode_follow  = core_mode_is(&self->mode, CORE_MODE_LINE_FOLLOWING);
    bool mode_changed = core_mode_changed(&self->mode);
    bool on_route     = core_position_is_on_route(&self->position);

    if (mode_follow && mode_changed)
    {
        core_port_route_guard_start();
    }

    if (mode_follow && on_route)
    {
        core_port_route_guard_reset();
    }

    if (!mode_follow && mode_changed)
    {
        core_port_route_guard_stop();
    }
}

void
core_vehicle_timeout_route_guard(core_vehicle_t *self)
{
    core_port_route_guard_stop();
    self->route_guard_timeout = true;
}

void
core_vehicle_update_motion(core_vehicle_t *self)
{
    core_motion_t motion = core_motion_create(self);
    bool is_mode_follow  = core_mode_is(&self->mode, CORE_MODE_LINE_FOLLOWING);
    bool motion_differs  = !core_motion_equals(&self->motion, &motion);

    bool is_update_following = is_mode_follow && !self->position_handeled;
    bool is_update_manual    = !is_mode_follow && motion_differs;

    if (is_update_following || is_update_manual)
    {
        self->motion            = motion;
        self->position_handeled = true;
        core_port_motion_apply(&self->motion);
    }
}

void
core_vehicle_update_state_indicator(core_vehicle_t *self)
{
    if (core_mode_changed(&self->mode))
    {
        core_port_mode_indicator_apply(core_mode_get(&self->mode));
    }
}

static inline void
mode_transit_from_line_detected(core_vehicle_t *self)
{
    if (!core_position_is_on_route(&self->position))
    {
        core_mode_set(&self->mode, CORE_MODE_MANUAL);
    }
    else if (core_control_has(&self->control, CORE_CONTROL_FOLLOW))
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
    if (core_control_has(&self->control, CORE_CONTROL_BREAK))
    {
        core_mode_set(&self->mode, CORE_MODE_MANUAL);
    }
    else if (self->route_guard_timeout)
    {
        self->route_guard_timeout = false;
        core_control_t control = core_control_create(CORE_CONTROL_NONE);
        core_mode_set(&self->mode, CORE_MODE_MANUAL);
        core_vehicle_update_control(self, control);
    }
    else
    {
        core_mode_set(&self->mode, CORE_MODE_LINE_FOLLOWING);
    }
}

static inline void
mode_transit_from_manual(core_vehicle_t *self)
{
    if (core_position_is_on_route(&self->position))
    {
        core_mode_set(&self->mode, CORE_MODE_LINE_DETECTED);
    }
    else
    {
        core_mode_set(&self->mode, CORE_MODE_MANUAL);
    }
}