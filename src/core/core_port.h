#ifndef _CORE_PORTS_H
#define _CORE_PORTS_H

#include "core_type.h"

void
core_port_motion_init(void);

void
core_port_motion_apply(core_motion_t *motion);

#endif