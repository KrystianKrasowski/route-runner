#ifndef _CORE_TASKS_H
#define _CORE_TASKS_H

#include "vehicle.h"

void
core_task_remote_control_receive(core_vehicle_t *vehicle);

void
core_task_line_position_receive(core_vehicle_t *vehicle);

void
core_task_vehicle_state_update(core_vehicle_t *vehicle);

void
core_task_motion_update(core_vehicle_t *vehicle);

void
core_task_state_indicator_update(core_vehicle_t *vehicle);

void
core_task_debug(core_vehicle_t *vehicle);

#endif