#include <linebot_port_mock_motion.h>
#include <string.h>

typedef struct
{
    linebot_motion_t applied_motion;
    int              calls;
} mock_motion_t;

static mock_motion_t mock;

void
linebot_port_motion_init(void)
{}

void
linebot_port_motion_apply(linebot_motion_t motion)
{
    mock.applied_motion = motion;
    mock.calls++;
}

void
linebot_port_mock_motion_init(void)
{
    memset(&mock.applied_motion, 0, sizeof(mock.applied_motion));
    mock.calls = 0;
}

bool
linebot_port_mock_motion_verify_applied(void)
{
    return mock.calls > 0;
}

linebot_motion_t
linebot_port_mock_motion_get_applied(void)
{
    return mock.applied_motion;
}

int
linebot_port_mock_motion_verify_apply_calls(void)
{
    return mock.calls;
}