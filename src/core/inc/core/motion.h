#ifndef _CORE_MOTION_H
#define _CORE_MOTION_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    CORE_MOTION_NONE,
    CORE_MOTION_FORWARD,
    CORE_MOTION_BACKWARD,
} core_motion_direction_t;

typedef struct
{
    core_motion_direction_t direction;
    int8_t                  correction;
} core_motion_t;

core_motion_t
core_motion(core_motion_direction_t direction, int8_t correction);

bool
core_motion_equals(core_motion_t *self, core_motion_t *other);

core_motion_direction_t
core_motion_get_direction(core_motion_t *self);

int8_t
core_motion_get_correction(core_motion_t *self);

#endif