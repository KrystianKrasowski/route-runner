#include "core/tasks.h"
#include "core/ports.h"

void
core_task_debug(core_vehicle_t *vehicle)
{
    core_port_debug_apply(vehicle);
}