#include "core/control.h"
#include <string.h>

core_control_t
core_control_create(uint16_t commands)
{
    core_control_t control = {commands};
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