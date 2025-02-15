#include "core.h"

void
core_motion_init(core_motion_t *self)
{
    self->direction = CORE_MOTION_NONE;
    self->angle     = 0;
}

bool
core_motion_equals(core_motion_t *self, core_motion_t *other)
{
    return self->angle == other->angle && self->direction == other->direction;
}