#include "core.h"
#include <string.h>

void
core_task_motion_update(core_vehicle_t *vehicle)
{
    if (core_vehicle_motion_update(vehicle) == CORE_VEHICLE_MOTION_CHANGED)
    {
        core_port_motion_apply(&vehicle->motion);
    }
}