#include "core_motion_factory.h"

static inline core_motion_direction_t
create_manual_direction(core_control_t *control);

static inline int8_t
create_manual_correction(core_control_t *control);

core_motion_t
core_motion_create_by_control(core_control_t *control)
{
    int8_t                  correction = create_manual_correction(control);
    core_motion_direction_t direction  = create_manual_direction(control);
    core_motion_t           motion     = core_motion(direction, correction);

    return motion;
}

core_motion_t
core_motion_create_by_position(core_position_t *position)
{

    int8_t        correction = core_position_regulate(position);
    core_motion_t motion     = core_motion(CORE_MOTION_FORWARD, correction);

    return motion;
}

static inline core_motion_direction_t
create_manual_direction(core_control_t *control)
{
    if (core_control_has(control, CORE_CONTROL_FORWARD))
    {
        return CORE_MOTION_FORWARD;
    }
    else if (core_control_has(control, CORE_CONTROL_BACKWARD))
    {
        return CORE_MOTION_BACKWARD;
    }
    else
    {
        return CORE_MOTION_NONE;
    }
}

static inline int8_t
create_manual_correction(core_control_t *control)
{
    if (core_control_has(control, CORE_CONTROL_LEFT))
    {
        return -50;
    }
    else if (core_control_has(control, CORE_CONTROL_RIGHT))
    {
        return 50;
    }
    else
    {
        return 0;
    }
}