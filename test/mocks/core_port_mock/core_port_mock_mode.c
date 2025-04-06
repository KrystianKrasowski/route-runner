#include "core_port_mock_mode.h"
#include <core/ports.h>

typedef struct
{
    int         calls;
    core_mode_t applied_mode;
} mock_state_indicator_t;

static mock_state_indicator_t mock;

void
core_port_mode_changed(core_mode_t *mode)
{
    mock.calls++;
    mock.applied_mode = *mode;
}

void
core_port_mock_mode_init(void)
{
    mock.calls = 0;
}

int
core_port_mock_mode_verify_changed_calls(void)
{
    return mock.calls;
}

core_mode_t
core_port_mock_mode_get_changed_mode(void)
{
    return mock.applied_mode;
}