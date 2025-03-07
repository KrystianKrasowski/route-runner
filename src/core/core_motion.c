#include "core/motion.h"

void
core_motion_init(core_motion_t *self)
{
    self->direction  = CORE_MOTION_NONE;
    self->correction = 0;
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

void
core_motion_set_direction(core_motion_t          *self,
                          core_motion_direction_t direction)
{
    self->direction = direction;
}

int8_t
core_motion_get_correction(core_motion_t *self)
{
    return self->correction;
}

void
core_motion_set_correction(core_motion_t *self, int8_t correction)
{
    self->correction = correction;
}