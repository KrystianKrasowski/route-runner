#include "core.h"

void
core_task_state_indicator_update(core_vehicle_t *vehicle)
{
    core_port_state_indicator_apply(vehicle->state);
}