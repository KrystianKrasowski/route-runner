#ifndef _CORE_PORTS_H
#define _CORE_PORTS_H

#include "core_type.h"

void
core_port_remote_control_init(void);

uint16_t
core_port_remote_control_map(uint16_t raw_command);

void
core_port_motion_init(void);

void
core_port_motion_apply(core_motion_t *motion);

#endif