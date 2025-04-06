#include "core/mode.h"
#include <string.h>

core_mode_t
core_mode(core_mode_value_t value)
{
    core_mode_t mode;
    mode.value = value;

    return mode;
}

bool
core_mode_equals(core_mode_t *self, core_mode_t *other)
{
    return self->value == other->value;
}

core_mode_value_t
core_mode_get(core_mode_t *self)
{
    return self->value;
}

bool
core_mode_is_following(core_mode_t *self)
{
    return self->value == CORE_MODE_FOLLOWING;
}

core_mode_t
core_mode_compute_by_control(core_mode_t *self, core_control_t control)
{
    bool is_mode_detected  = self->value == CORE_MODE_DETECTED;
    bool is_mode_following = self->value == CORE_MODE_FOLLOWING;
    bool is_command_follow = core_control_has(&control, CORE_CONTROL_FOLLOW);
    bool is_command_break  = core_control_has(&control, CORE_CONTROL_BREAK);

    if (is_mode_detected && is_command_follow)
    {
        return core_mode(CORE_MODE_FOLLOWING);
    }
    else if (is_mode_following && is_command_break)
    {
        return core_mode(CORE_MODE_MANUAL);
    }
    else
    {
        return *self;
    }
}

core_mode_t
core_mode_compute_by_coords(core_mode_t *self, core_coords_t coords)
{
    bool is_mode_manual   = self->value == CORE_MODE_MANUAL;
    bool is_mode_detected = self->value == CORE_MODE_DETECTED;
    bool is_on_route      = core_coords_are_on_route(&coords);

    if (is_mode_manual && is_on_route)
    {
        return core_mode(CORE_MODE_DETECTED);
    }
    else if (is_mode_detected && !is_on_route)
    {
        return core_mode(CORE_MODE_MANUAL);
    }
    else
    {
        return *self;
    }
}