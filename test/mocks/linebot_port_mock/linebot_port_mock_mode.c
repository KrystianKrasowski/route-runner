#include <linebot_port_mock_mode.h>

typedef struct
{
    int            calls;
    linebot_mode_t applied_mode;
} mock_state_indicator_t;

static mock_state_indicator_t mock;

void
linebot_port_mode_init(void)
{
}

void
linebot_port_mode_changed(linebot_mode_t const value)
{
    mock.calls++;
    mock.applied_mode = value;
}

void
linebot_port_mock_mode_init(void)
{
    mock.calls = 0;
}

int
linebot_port_mock_mode_verify_changed_calls(void)
{
    return mock.calls;
}

linebot_mode_t
linebot_port_mock_mode_get_changed_mode(void)
{
    return mock.applied_mode;
}