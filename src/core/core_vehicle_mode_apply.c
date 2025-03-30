#include "core_vehicle_mode_apply.h"
#include "core/types.h"

static inline void
transit_from_manual(core_vehicle_t *vehicle);

static inline void
transit_from_line_detected(core_vehicle_t *vehicle);

static inline void
transit_from_line_following(core_vehicle_t *vehicle);

bool
core_vehicle_mode_apply(core_vehicle_t *vehicle)
{
    core_mode_value_t value = core_vehicle_get_mode_value(vehicle);

    switch (value)
    {
        case CORE_MODE_LINE_DETECTED:
            transit_from_line_detected(vehicle);
            break;
        case CORE_MODE_LINE_FOLLOWING:
            transit_from_line_following(vehicle);
            break;
        case CORE_MODE_MANUAL:
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
        core_vehicle_set_mode_value(vehicle, CORE_MODE_LINE_DETECTED);
    }
    else
    {
        core_vehicle_set_mode_value(vehicle, CORE_MODE_MANUAL);
    }
}

static inline void
transit_from_line_detected(core_vehicle_t *vehicle)
{
    if (!core_vehicle_is_line_detected(vehicle))
    {
        core_vehicle_set_mode_value(vehicle, CORE_MODE_MANUAL);
    }
    else if (core_vehicle_get_command(vehicle) == CORE_REMOTE_CONTROL_FOLLOW)
    {
        core_vehicle_set_mode_value(vehicle, CORE_MODE_LINE_FOLLOWING);
    }
    else
    {
        core_vehicle_set_mode_value(vehicle, CORE_MODE_LINE_DETECTED);
    }
}

static inline void
transit_from_line_following(core_vehicle_t *vehicle)
{
    if (core_vehicle_get_command(vehicle) == CORE_REMOTE_CONTROL_BREAK)
    {
        core_vehicle_set_mode_value(vehicle, CORE_MODE_MANUAL);
    }
    else if (core_vehicle_is_line_lost(vehicle))
    {
        core_vehicle_set_mode_value(vehicle, CORE_MODE_MANUAL);
        core_vehicle_update_command(vehicle, CORE_REMOTE_CONTROL_NONE);
    }
    else
    {
        core_vehicle_set_mode_value(vehicle, CORE_MODE_LINE_FOLLOWING);
    }
}