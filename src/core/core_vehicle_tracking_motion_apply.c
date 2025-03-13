#include "core_vehicle_tracking_motion_apply.h"

// 1,2ms
// kp 0.4; ki 0.015; kd 5.5
// kp 0.4; ki 0.016; kd 5.52
// kp 0.38; ki 0.018; kd 5.545
// kp 0.385; ki 0.019; kd 5.547
// kp 0.385; ki 0.019; kd 5.57
// kp 0.385; ki 0.02; kd 5.57
// 1ms
// kp 0.385; ki 0.02; kd 5.572
// kp 0.388; ki 0.024; kd 5.573
// kp 0.328; ki 0.024; kd 5.573 !!
// 1.3ms

#define KP 0.328
#define KI 0.024
#define KD 5.573

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