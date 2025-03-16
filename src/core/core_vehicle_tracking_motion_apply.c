#include "core_vehicle_tracking_motion_apply.h"

#define KP 0.7
#define KI 0
#define KD 2.25

static inline int8_t
pid_regulation(core_vehicle_t *vehicle);

core_vehicle_result_t
core_vehicle_tracking_motion_apply(core_vehicle_t *vehicle)
{
    if (!core_vehicle_is_position_updated(vehicle))
    {
        int8_t correction = pid_regulation(vehicle);
        core_vehicle_set_motion_direction(vehicle, CORE_MOTION_FORWARD);
        core_vehicle_set_motion_correction(vehicle, correction);
        core_vehicle_set_position_updated(vehicle, true);
        return CORE_VEHICLE_MOTION_CHANGED;
    }
    else
    {
        return CORE_VEHICLE_MOTION_REMAINS;
    }
}

static inline int8_t
pid_regulation(core_vehicle_t *vehicle)
{
    int8_t  previous   = core_vehicle_get_position_error(vehicle);
    int8_t  error      = core_vehicle_update_position_error(vehicle);
    int16_t all_errors = core_vehicle_get_position_errors_sum(vehicle);

    int16_t correction = KP * error + KI * all_errors + KD * (error - previous);

    if (correction > 100)
    {
        return 100;
    }
    else if (correction < -100)
    {
        return -100;
    }
    else
    {
        return correction;
    }
}