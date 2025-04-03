#include "core_port_mock_mode_indicator.h"
#include <core/ports.h>

typedef struct
{
    int calls;
} mock_state_indicator_t;

static mock_state_indicator_t mock;

void
core_port_mode_indicator_apply(core_mode_value_t value)
{
    mock.calls++;
}

void
core_port_mock_mode_indicator_init(void)
{
    mock.calls = 0;
}

int
core_port_mock_mode_indicator_verify_apply_calls(void)
{
    return mock.calls;
}