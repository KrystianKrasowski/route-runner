#ifndef _CORE_TYPES_H
#define _CORE_TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    CORE_CONTROL_NONE     = 0,
    CORE_CONTROL_FORWARD  = 1,
    CORE_CONTROL_BACKWARD = 2,
    CORE_CONTROL_LEFT     = 4,
    CORE_CONTROL_RIGHT    = 8,
    CORE_CONTROL_BREAK    = 16,
    CORE_CONTROL_FOLLOW   = 32,
} core_control_command_t;

typedef struct core_control
{
    uint16_t commands;
} core_control_t;

core_control_t
core_control_create(uint16_t commands);

uint16_t
core_control_get_commands(core_control_t *self);

void
core_control_set_commands(core_control_t *self, uint16_t commands);

bool
core_control_has(core_control_t *self, core_control_command_t command);

void
core_control_truncate(core_control_t *self, uint16_t commands);

#endif