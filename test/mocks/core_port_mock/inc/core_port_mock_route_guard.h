#ifndef _CORE_PORT_MOCK_ROUTE_GUARD_H
#define _CORE_PORT_MOCK_ROUTE_GUARD_H

void
core_port_mock_route_guard_init(void);

int
core_port_mock_route_guard_verify_start_calls(void);

int
core_port_mock_route_guard_verify_reset_calls(void);

int
core_port_mock_route_guard_verify_stop_calls(void);

#endif