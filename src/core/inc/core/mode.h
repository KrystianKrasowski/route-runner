#ifndef _CORE_MODE_H
#define _CORE_MODE_H

#include "control.h"
#include "coords.h"
#include <stdbool.h>

typedef enum
{
    CORE_MODE_MANUAL,
    CORE_MODE_LINE_DETECTED,
    CORE_MODE_LINE_FOLLOWING,
} core_mode_value_t;

typedef struct core_mode
{
    core_mode_value_t value;
} core_mode_t;

core_mode_t
core_mode(core_mode_value_t value);

bool
core_mode_equals(core_mode_t *self, core_mode_t *other);

core_mode_value_t
core_mode_get(core_mode_t *self);

bool
core_mode_is(core_mode_t *self, core_mode_value_t value);

core_mode_t
core_mode_compute_by_control(core_mode_t *self, core_control_t control);

core_mode_t
core_mode_compute_by_coords(core_mode_t *self, core_coords_t coords);

#endif