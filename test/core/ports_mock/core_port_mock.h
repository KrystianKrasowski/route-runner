#ifndef _CORE_PORT_MOCK_H
#define _CORE_PORT_MOCK_H

#include <core_type.h>
#include <stdbool.h>

void
core_port_mock_reset(void);

bool
core_port_mock_verify_motion_applied(void);

core_motion_t
core_port_mock_get_motion_applied(void);

#endif