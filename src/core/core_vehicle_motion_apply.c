#include "core_vehicle_motion_apply.h"
#include "core/types.h"

#define KP 1

static inline void
set_motion_correction(core_vehicle_t *self, core_motion_t *motion);

static inline void
set_motion_direction(core_vehicle_t *self, core_motion_t *motion);

static inline int8_t
pid_regulation(core_vehicle_t *vehicle);

core_vehicle_result_t
core_vehicle_motion_apply(core_vehicle_t *vehicle)
{
    if (core_vehicle_get_state(vehicle) == CORE_VEHICLE_STATE_LINE_FOLLOWING)
    {
        core_vehicle_update_position_error(vehicle);

        int8_t error = core_vehicle_get_position_error(vehicle);

        core_vehicle_set_motion_direction(vehicle, CORE_MOTION_FORWARD);
        core_vehicle_set_motion_correction(vehicle, error);
    }
    else
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

static inline int8_t
pid_regulation(core_vehicle_t *vehicle)
{
    int8_t error = core_vehicle_update_position_error(vehicle);

    int8_t correction = KP * error;

    core_vehicle_set_motion_direction(vehicle, CORE_MOTION_FORWARD);
    core_vehicle_set_motion_correction(vehicle, correction);
}