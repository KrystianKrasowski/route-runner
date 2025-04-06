#ifndef _CORE_PORTS_MOCK_STATE_INDICATOR_H
#define _CORE_PORTS_MOCK_STATE_INDICATOR_H

#include <core/mode.h>

void
core_port_mock_mode_init(void);

int
core_port_mock_mode_verify_changed_calls(void);

core_mode_value_t
core_port_mock_mode_indicator_get_applied_mode_value(void);

core_mode_t
core_port_mock_mode_get_changed_mode(void);

#endif