#ifndef _CORE_MODE_H
#define _CORE_MODE_H

#include <stdbool.h>
#include <utils/stack.h>

typedef enum
{
    CORE_MODE_MANUAL,
    CORE_MODE_LINE_DETECTED,
    CORE_MODE_LINE_FOLLOWING,
} core_mode_value_t;

typedef struct core_mode
{
    stack_t value;
} core_mode_t;

void
core_mode_init(core_mode_t *self);

void
core_mode_set(core_mode_t *self, core_mode_value_t value);

core_mode_value_t
core_mode_get(core_mode_t *self);

bool
core_mode_changed(core_mode_t *self);

bool
core_mode_is(core_mode_t *self, core_mode_value_t value);

#endif