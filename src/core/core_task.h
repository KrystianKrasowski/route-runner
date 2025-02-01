#ifndef _CORE_TASK_H
#define _CORE_TASK_H

#include "core_type.h"

void
core_task_remote_control_receive(core_vehicle_t *vehicle);

void
core_task_motion_update(core_vehicle_t *vehicle);

#endif