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
core_mode_is_tracking(core_mode_t *self)
{
    return core_mode_is_following(self) || core_mode_is_recovering(self);
}

bool
core_mode_is_detected(core_mode_t *self)
{
    return CORE_MODE_DETECTED == self->value;
}

bool
core_mode_is_manual(core_mode_t *self)
{
    return CORE_MODE_MANUAL == self->value;
}

bool
core_mode_is_following(core_mode_t *self)
{
    return CORE_MODE_FOLLOWING == self->value;
}

bool
core_mode_is_recovering(core_mode_t *self)
{
    return CORE_MODE_RECOVERING == self->value;
}

core_mode_t
core_mode_compute_by_control(core_mode_t *self, core_control_t control)
{
    bool is_command_follow = core_control_has(&control, CORE_CONTROL_FOLLOW);
    bool is_command_break  = core_control_has(&control, CORE_CONTROL_BREAK);

    if (core_mode_is_detected(self) && is_command_follow)
    {
        return core_mode(CORE_MODE_FOLLOWING);
    }
    else if (core_mode_is_tracking(self) && is_command_break)
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
    bool is_on_route = core_coords_is_on_route(&coords);
    bool is_on_finish = core_coords_is_on_finish(&coords);

    if (core_mode_is_manual(self) && is_on_route)
    {
        return core_mode(CORE_MODE_DETECTED);
    }
    else if (core_mode_is_detected(self) && !is_on_route)
    {
        return core_mode(CORE_MODE_MANUAL);
    }
    else if (core_mode_is_tracking(self) && is_on_finish)
    {
        return core_mode(CORE_MODE_MANUAL);
    }
    else if (core_mode_is_following(self) && !is_on_route)
    {
        return core_mode(CORE_MODE_RECOVERING);
    }
    else if (core_mode_is_recovering(self) && is_on_route)
    {
        return core_mode(CORE_MODE_FOLLOWING);
    }
    else
    {
        return *self;
    }
}