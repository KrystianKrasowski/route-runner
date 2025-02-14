#include "core.h"

void
core_task_state_indicator_update(core_vehicle_t *vehicle)
{
    if (core_vehicle_is_state_changed(vehicle))
    {
        core_vehicle_state_t state = core_vehicle_get_state(vehicle);
        core_port_state_indicator_apply(state);
    }
}