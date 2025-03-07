#ifndef _CORE_VEHICLE_COMMAND_APPLY_H
#define _CORE_VEHICLE_COMMAND_APPLY_H

#include "core/vehicle.h"
#include <stdbool.h>
#include <stdint.h>

bool
core_vehicle_command_apply(core_vehicle_t *vehicle, uint16_t command);

#endif