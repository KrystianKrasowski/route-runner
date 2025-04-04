#include "core/motion.h"

core_motion_t
core_motion(core_motion_direction_t direction, int8_t correction)
{
    core_motion_t motion;
    motion.direction  = direction;
    motion.correction = correction;

    return motion;
}

bool
core_motion_equals(core_motion_t *self, core_motion_t *other)
{
    return self->correction == other->correction &&
           self->direction == other->direction;
}

core_motion_direction_t
core_motion_get_direction(core_motion_t *self)
{
    return self->direction;
}

int8_t
core_motion_get_correction(core_motion_t *self)
{
    return self->correction;
}