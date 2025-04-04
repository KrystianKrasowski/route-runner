#include "core/mode.h"
#include <string.h>

core_mode_t
core_mode(core_mode_value_t value)
{
    core_mode_t mode;
    core_mode_init(&mode);
    core_mode_set(&mode, value);

    return mode;
}

bool
core_mode_equals(core_mode_t *self, core_mode_t *other)
{
    return self->mode_value == other->mode_value;
}

void
core_mode_init(core_mode_t *self)
{
    memset(self, 0, sizeof(*self));

    stack_t value;
    stack_init(&value, 2);
    stack_push(&value, CORE_MODE_MANUAL);

    self->value      = value;
    self->mode_value = CORE_MODE_MANUAL;
}

void
core_mode_set(core_mode_t *self, core_mode_value_t value)
{
    stack_push_rolling(&self->value, value);
    self->mode_value = value;
}

core_mode_value_t
core_mode_get(core_mode_t *self)
{
    return self->mode_value;
}

bool
core_mode_changed(core_mode_t *self)
{
    int16_t bottom;
    int16_t top;

    stack_peek_bottom(&self->value, &bottom);
    stack_peek(&self->value, &top);

    return stack_get_length(&self->value) == 1 || bottom != top;
}

bool
core_mode_is(core_mode_t *self, core_mode_value_t value)
{
    return self->mode_value == value;
}

core_mode_t
core_mode_compute_by_control(core_mode_t *self, core_control_t control)
{
    bool is_mode_detected  = self->mode_value == CORE_MODE_LINE_DETECTED;
    bool is_mode_following = self->mode_value == CORE_MODE_LINE_FOLLOWING;
    bool is_command_follow = core_control_has(&control, CORE_CONTROL_FOLLOW);
    bool is_command_break  = core_control_has(&control, CORE_CONTROL_BREAK);

    if (is_mode_detected && is_command_follow)
    {
        return core_mode(CORE_MODE_LINE_FOLLOWING);
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
    bool is_mode_manual   = self->mode_value == CORE_MODE_MANUAL;
    bool is_mode_detected = self->mode_value == CORE_MODE_LINE_DETECTED;
    bool is_on_route      = core_coords_are_on_route(&coords);

    if (is_mode_manual && is_on_route)
    {
        return core_mode(CORE_MODE_LINE_DETECTED);
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