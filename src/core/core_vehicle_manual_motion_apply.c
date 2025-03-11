#include "core_vehicle_manual_motion_apply.h"
#include "core/types.h"

static inline void
set_motion_correction(core_vehicle_t *self, core_motion_t *motion);

static inline void
set_motion_direction(core_vehicle_t *self, core_motion_t *motion);

core_vehicle_result_t
core_vehicle_manual_motion_apply(core_vehicle_t *vehicle)
{
    core_motion_t motion;
    core_motion_init(&motion);

    set_motion_correction(vehicle, &motion);
    set_motion_direction(vehicle, &motion);

    if (core_vehicle_motion_differs(vehicle, &motion))
    {
        core_vehicle_set_motion(vehicle, motion);
        return CORE_VEHICLE_MOTION_CHANGED;
    }
    else
    {
        return CORE_VEHICLE_MOTION_REMAINS;
    }
}

static inline void
set_motion_correction(core_vehicle_t *vehicle, core_motion_t *motion)
{
    if (core_vehicle_is_commanded(vehicle, CORE_REMOTE_CONTROL_LEFT))
    {
        core_motion_set_correction(motion, -90);
    }
    else if (core_vehicle_is_commanded(vehicle, CORE_REMOTE_CONTROL_RIGHT))
    {
        core_motion_set_correction(motion, 90);
    }
    else
    {
        core_motion_set_correction(motion, 0);
    }
}

static inline void
set_motion_direction(core_vehicle_t *vehicle, core_motion_t *motion)
{
    if (core_vehicle_is_commanded(vehicle, CORE_REMOTE_CONTROL_FORWARD))
    {
        core_motion_set_direction(motion, CORE_MOTION_FORWARD);
    }
    else if (core_vehicle_is_commanded(vehicle, CORE_REMOTE_CONTROL_BACKWARD))
    {
        core_motion_set_direction(motion, CORE_MOTION_BACKWARD);
    }
    else
    {
        core_motion_set_direction(motion, CORE_MOTION_NONE);
        core_motion_set_correction(motion, 0);
    }
}