#include "core.h"

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