#include "core/control.h"
#include <string.h>

static inline bool
are_valid(uint16_t commands);

core_control_t
core_control(uint16_t commands)
{
    core_control_t control;

    if (are_valid(commands))
    {
        control.commands = commands;
    }
    else
    {
        control.commands = CORE_CONTROL_NONE;
    }

    return control;
}

uint16_t
core_control_get_commands(core_control_t *self)
{
    return self->commands;
}

void
core_control_set_commands(core_control_t *self, uint16_t commands)
{
    self->commands = commands;
}

bool
core_control_has(core_control_t *self, core_control_command_t command)
{
    return self->commands & command;
}

void
core_control_truncate(core_control_t *self, uint16_t commands)
{
    self->commands &= ~commands;
}

static inline bool
are_valid(uint16_t commands)
{
    bool forward  = commands & CORE_CONTROL_FORWARD;
    bool backward = commands & CORE_CONTROL_BACKWARD;
    bool left     = commands & CORE_CONTROL_LEFT;
    bool right    = commands & CORE_CONTROL_RIGHT;
    bool follow   = commands & CORE_CONTROL_FOLLOW;
    bool breaks   = commands & CORE_CONTROL_BREAK;
    bool none     = commands & CORE_CONTROL_NONE;

    return (forward && !backward) || (!forward && backward) ||
           (left && !right) || (!left && right) || follow || breaks || none;
}