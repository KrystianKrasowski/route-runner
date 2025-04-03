#ifndef _CORE_PORTS_MOCK_MOTION_H
#define _CORE_PORTS_MOCK_MOTION_H

#include <core/motion.h>

void
core_port_mock_motion_init(void);

bool
core_port_motion_mock_verify_applied(void);

core_motion_t
core_port_motion_mock_get_applied(void);

int
core_port_motion_mock_verify_apply_calls(void);

#endif