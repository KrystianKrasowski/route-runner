#include "core_vehicle_motion_apply.h"
#include "core/types.h"

static inline void
set_motion_correction(core_vehicle_t *self, core_motion_t *motion);

static inline void
set_motion_direction(core_vehicle_t *self, core_motion_t *motion);

core_vehicle_result_t
core_vehicle_motion_apply(core_vehicle_t *vehicle)
{
    core_motion_t motion;
    core_motion_init(&motion);
    set_motion_correction(vehicle, &motion);
    set_motion_direction(vehicle, &motion);

    if (!core_motion_equals(&vehicle->motion, &motion))
    {
        vehicle->motion = motion;
        return CORE_VEHICLE_MOTION_CHANGED;
    }
    else
    {
        return CORE_VEHICLE_MOTION_REMAINS;
    }
}

static inline void
set_motion_correction(core_vehicle_t *self, core_motion_t *motion)
{
    if (self->command & CORE_REMOTE_CONTROL_LEFT)
    {
        motion->correction = -90;
    }
    else if (self->command & CORE_REMOTE_CONTROL_RIGHT)
    {
        motion->correction = 90;
    }
    else
    {
        motion->correction = 0;
    }
}

static inline void
set_motion_direction(core_vehicle_t *self, core_motion_t *motion)
{
    if (self->command & CORE_REMOTE_CONTROL_FORWARD)
    {
        motion->direction = CORE_MOTION_FORWARD;
    }
    else if (self->command & CORE_REMOTE_CONTROL_BACKWARD)
    {
        motion->direction = CORE_MOTION_BACKWARD;
    }
    else
    {
        motion->direction  = CORE_MOTION_NONE;
        motion->correction = 0;
    }
}