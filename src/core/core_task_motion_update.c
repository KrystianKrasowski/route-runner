#include "core_port.h"
#include "core_task.h"
#include <string.h>

static core_motion_t
resolve_motion_by_remote_control(uint16_t command);

void
core_task_motion_update(core_vehicle_t *vehicle)
{
    core_motion_t motion = resolve_motion_by_remote_control(vehicle->command);

    if (motion.direction != vehicle->motion.direction ||
        motion.angle != vehicle->motion.angle)
    {
        vehicle->motion = motion;
        core_port_motion_apply(&vehicle->motion);
    }
}

static core_motion_t
resolve_motion_by_remote_control(uint16_t command)
{
    core_motion_t motion;
    memset(&motion, 0, sizeof(motion));

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