#include "core/ports.h"
#include "core/vehicle.h"
#include "core_motion_factory.h"
#include <string.h>

void
core_vehicle_init(core_vehicle_t *self)
{
    memset(self, 0, sizeof(*self));
    core_position_init(&self->position);
    core_mode_init(&self->mode);
}

core_mode_t
core_vehicle_get_mode(core_vehicle_t *self)
{
    return self->mode;
}

void
core_vehicle_set_mode(core_vehicle_t *self, core_mode_t mode)
{
    self->mode = mode;
}

void
core_vehicle_apply_manual_motion(core_vehicle_t *self, core_control_t control)
{
    bool is_following    = core_mode_is(&self->mode, CORE_MODE_LINE_FOLLOWING);
    bool is_break        = core_control_has(&control, CORE_CONTROL_BREAK);
    core_motion_t motion = core_motion_create_by_control(&control);

    if (!is_following || is_break)
    {
        core_port_motion_apply(&motion);
    }
}

void
core_vehicle_apply_following_motion(core_vehicle_t *self, core_coords_t coords)
{
    bool is_following = core_mode_is(&self->mode, CORE_MODE_LINE_FOLLOWING);

    if (is_following)
    {
        core_position_update_coords(&self->position, coords);
        core_motion_t motion = core_motion_create_by_position(&self->position);
        core_port_motion_apply(&motion);
    }
}

void
core_vehicle_timeout_route_guard(core_vehicle_t *self)
{
    self->mode           = core_mode(CORE_MODE_MANUAL);
    core_motion_t motion = core_motion(CORE_MOTION_NONE, 0);
    core_port_motion_apply(&motion);
    core_port_mode_indicator_apply(CORE_MODE_MANUAL);
    core_port_route_guard_stop();
}

void
core_vehicle_change_mode_by_control(core_vehicle_t *self,
                                    core_control_t  control)
{
    core_mode_t mode = core_mode_compute_by_control(&self->mode, control);

    if (!core_mode_equals(&self->mode, &mode))
    {
        core_port_mode_indicator_apply(core_mode_get(&mode));

        if (core_mode_is(&mode, CORE_MODE_LINE_FOLLOWING))
        {
            core_port_route_guard_start();
        }
        else
        {
            core_port_route_guard_stop();
        }
    }

    self->mode = mode;
}

void
core_vehicle_change_mode_by_coords(core_vehicle_t *self, core_coords_t coords)
{
    core_mode_t mode       = core_mode_compute_by_coords(&self->mode, coords);
    bool is_mode_following = core_mode_is(&mode, CORE_MODE_LINE_FOLLOWING);
    bool is_on_route       = core_coords_are_on_route(&coords);

    if (is_mode_following && is_on_route)
    {
        core_port_route_guard_reset();
    }

    if (!core_mode_equals(&self->mode, &mode))
    {
        core_port_mode_indicator_apply(core_mode_get(&mode));
    }

    self->mode = mode;
}