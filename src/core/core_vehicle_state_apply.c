#include "core_vehicle_state_apply.h"
#include "core/types.h"

static inline void
transit_from_manual(core_vehicle_t *vehicle);

static inline void
transit_from_line_detected(core_vehicle_t *vehicle);

static inline void
transit_from_line_following(core_vehicle_t *vehicle);

bool
core_vehicle_state_apply(core_vehicle_t *vehicle)
{
    core_vehicle_state_t state = core_vehicle_get_state(vehicle);

    switch (state)
    {
        case CORE_VEHICLE_STATE_LINE_DETECTED:
            transit_from_line_detected(vehicle);
            break;
        case CORE_VEHICLE_STATE_LINE_FOLLOWING:
            transit_from_line_following(vehicle);
            break;
        case CORE_VEHICLE_STATE_MANUAL:
        default:
            transit_from_manual(vehicle);
            break;
    }

    return true;
}

static inline void
transit_from_manual(core_vehicle_t *vehicle)
{
    if (core_vehicle_is_line_detected(vehicle))
    {
        core_vehicle_set_state(vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    }
    else
    {
        core_vehicle_set_state(vehicle, CORE_VEHICLE_STATE_MANUAL);
    }
}

static inline void
transit_from_line_detected(core_vehicle_t *vehicle)
{
    if (!core_vehicle_is_line_detected(vehicle))
    {
        core_vehicle_set_state(vehicle, CORE_VEHICLE_STATE_MANUAL);
    }
    else if (core_vehicle_get_command(vehicle) == CORE_REMOTE_CONTROL_FOLLOW)
    {
        core_vehicle_set_state(vehicle, CORE_VEHICLE_STATE_LINE_FOLLOWING);
    }
    else
    {
        core_vehicle_set_state(vehicle, CORE_VEHICLE_STATE_LINE_DETECTED);
    }
}

static inline void
transit_from_line_following(core_vehicle_t *vehicle)
{
    if (core_vehicle_get_command(vehicle) == CORE_REMOTE_CONTROL_BREAK)
    {
        core_vehicle_set_state(vehicle, CORE_VEHICLE_STATE_MANUAL);
    }
    else if (!core_vehicle_is_line_detected(vehicle))
    {
        core_vehicle_set_state(vehicle, CORE_VEHICLE_STATE_MANUAL);
        core_vehicle_set_command(vehicle, CORE_REMOTE_CONTROL_NONE);
    }
    else
    {
        core_vehicle_set_state(vehicle, CORE_VEHICLE_STATE_LINE_FOLLOWING);
    }
}