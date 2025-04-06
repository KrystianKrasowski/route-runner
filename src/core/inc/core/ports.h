#ifndef _CORE_PORTS_H
#define _CORE_PORTS_H

#include "vehicle.h"
#include "motion.h"
#include <stdint.h>

void
core_port_control_init(void);

uint16_t
core_port_control_command_map(uint16_t raw_command);

void
core_port_coords_init(void);

core_coords_t
core_port_coords_map(uint8_t *raw);

void
core_port_motion_init(void);

void
core_port_motion_apply(core_motion_t *motion);

void
core_port_mode_init(void);

void
core_port_mode_changed(core_mode_t *value);

#endif