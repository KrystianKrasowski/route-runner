#include <pathbot/port.h>
#include <pathbot/port_mock_mode.h>

typedef struct
{
    int            changed_calls;
    pathbot_mode_t changed_mode;
} pathbot_port_mock_mode_t;

static pathbot_port_mock_mode_t mock;

void
pathbot_port_mode_changed(pathbot_mode_t const mode)
{
    mock.changed_calls++;
    mock.changed_mode = mode;
}

void
pathbot_port_mock_mode_reset(void)
{
    mock.changed_mode  = PATHBOT_MODE_MANUAL;
    mock.changed_calls = 0;
}

int
pathbot_port_mock_mode_verify_changed_calls(void)
{
    return mock.changed_calls;
}

pathbot_mode_t
pathbot_port_mock_mode_get_changed_mode(void)
{
    return mock.changed_mode;
}
