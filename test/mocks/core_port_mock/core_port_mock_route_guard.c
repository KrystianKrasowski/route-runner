#include "core_port_mock_route_guard.h"

typedef struct
{
    int start_calls;
    int reset_calls;
    int stop_calls;
} route_guard_mock_t;

static route_guard_mock_t mock;

void
core_port_route_guard_start(void)
{
    mock.start_calls++;
}

void
core_port_route_guard_reset(void)
{
    mock.reset_calls++;
}

void
core_port_route_guard_stop(void)
{
    mock.stop_calls++;
}

void
core_port_mock_route_guard_init(void)
{
    mock.start_calls = 0;
    mock.reset_calls = 0;
    mock.stop_calls  = 0;
}

int
core_port_mock_route_guard_verify_start_calls(void)
{
    return mock.start_calls;
}

int
core_port_mock_route_guard_verify_reset_calls(void)
{
    return mock.reset_calls;
}

int
core_port_mock_route_guard_verify_stop_calls(void)
{
    return mock.stop_calls;
}