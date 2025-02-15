#include "core.h"
#include <string.h>

static core_motion_t
resolve_motion_by_remote_control(uint16_t command);

void
core_task_motion_update(core_vehicle_t *vehicle)
{
    core_motion_t motion = resolve_motion_by_remote_control(vehicle->command);

    if (!core_motion_equals(&motion, &vehicle->motion))
    {
        vehicle->motion = motion;
        core_port_motion_apply(&vehicle->motion);
    }
}

static core_motion_t
resolve_motion_by_remote_control(uint16_t command)
{
    core_motion_t motion;
    core_motion_init(&motion);

    if (command & CORE_REMOTE_CONTROL_FORWARD)
    {
        motion.direction = CORE_MOTION_FORWARD;
    }
    else if (command & CORE_REMOTE_CONTROL_BACKWARD)
    {
        motion.direction = CORE_MOTION_BACKWARD;
    }
    else
    {
        motion.direction = CORE_MOTION_NONE;
        return motion;
    }

    if (command & CORE_REMOTE_CONTROL_LEFT)
    {
        motion.angle = -90;
    }
    else if (command & CORE_REMOTE_CONTROL_RIGHT)
    {
        motion.angle = 90;
    }
    else
    {
        motion.angle = 0;
    }

    return motion;
}