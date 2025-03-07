#ifndef _CORE_REMOTE_CONTROL_APPLY_CHAIN_H
#define _CORE_REMOTE_CONTROL_APPLY_CHAIN_H

#include "core/vehicle.h"
#include <stdbool.h>
#include <stdint.h>

bool
core_remote_control_apply(core_vehicle_t *vehicle, uint16_t command);

#endif