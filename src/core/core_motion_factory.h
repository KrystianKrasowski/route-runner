#ifndef _CORE_MOTION_FACTORY_H
#define _CORE_MOTION_FACTORY_H

#include "core/vehicle.h"

core_motion_t
core_motion_create(core_vehicle_t *vehicle);

core_motion_t
core_motion_create_by_control(core_control_t *control);

core_motion_t
core_motion_create_by_position(core_position_t *position);

#endif