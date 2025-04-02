#include "core_motion_factory.h"

static inline core_motion_t
create_tracking(core_vehicle_t *vehicle);

static inline core_motion_t
create_manual(core_vehicle_t *vehicle);

static inline core_motion_direction_t
create_manual_direction(core_vehicle_t *vehicle);

static inline int8_t
create_manual_correction(core_vehicle_t *vehicl);

core_motion_t
core_motion_create(core_vehicle_t *vehicle)
{
    switch (core_vehicle_get_mode_value(vehicle))
    {
        case CORE_MODE_LINE_FOLLOWING:
            return create_tracking(vehicle);
        default:
            return create_manual(vehicle);
    }
}

static inline core_motion_t
create_tracking(core_vehicle_t *vehicle)
{
    core_motion_t motion;

    int8_t correction = core_vehicle_position_regulate(vehicle);
    core_motion_set_correction(&motion, correction);
    core_motion_set_direction(&motion, CORE_MOTION_FORWARD);

    return motion;
}

static inline core_motion_t
create_manual(core_vehicle_t *vehicle)
{
    core_motion_t           motion;
    int8_t                  correction = create_manual_correction(vehicle);
    core_motion_direction_t direction  = create_manual_direction(vehicle);

    core_motion_set_correction(&motion, correction);
    core_motion_set_direction(&motion, direction);

    return motion;
}

static inline core_motion_direction_t
create_manual_direction(core_vehicle_t *vehicle)
{
    if (core_vehicle_has_command(vehicle, CORE_CONTROL_FORWARD))
    {
        return CORE_MOTION_FORWARD;
    }
    else if (core_vehicle_has_command(vehicle, CORE_CONTROL_BACKWARD))
    {
        return CORE_MOTION_BACKWARD;
    }
    else
    {
        return CORE_MOTION_NONE;
    }
}

static inline int8_t
create_manual_correction(core_vehicle_t *vehicle)
{
    if (core_vehicle_has_command(vehicle, CORE_CONTROL_LEFT))
    {
        return -50;
    }
    else if (core_vehicle_has_command(vehicle, CORE_CONTROL_RIGHT))
    {
        return 50;
    }
    else
    {
        return 0;
    }
}