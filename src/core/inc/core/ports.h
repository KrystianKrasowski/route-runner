#ifndef _CORE_PORTS_H
#define _CORE_PORTS_H

#include "vehicle.h"
#include <stdint.h>

void
core_port_remote_control_init(void);

uint16_t
core_port_remote_control_map(uint16_t raw_command);

void
core_port_coords_init(void);

core_coords_t
core_port_coords_map(uint8_t *raw);

void
core_port_motion_init(void);

void
core_port_motion_apply(core_vehicle_t *vehicle);

void
core_port_mode_indicator_init(void);

void
core_port_mode_indicator_apply(core_mode_t mode);

void
core_port_debug_init(void);

void
core_port_debug_apply(core_vehicle_t *vehicle);

#endif