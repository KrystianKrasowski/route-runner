#include <linebot_port_mock_motion.h>
#include <string.h>

typedef struct
{
    linebot_motion_direction_t applied_direction;
    int8_t                     applied_correction;
    int                        calls;
} mock_motion_t;

static mock_motion_t mock;

void
linebot_port_motion_init(void)
{
}

void
linebot_port_motion_apply(linebot_motion_t motion)
{
    mock.applied_direction  = linebot_get_motion_direction(motion);
    mock.applied_correction = linebot_get_motion_correction(motion);
    mock.calls++;
}

void
linebot_port_mock_motion_init(void)
{
    memset(&mock, 0, sizeof(mock));
    mock.calls = 0;
}

bool
linebot_port_mock_motion_verify_applied(void)
{
    return mock.calls > 0;
}

linebot_motion_direction_t
linebot_port_mock_motion_get_direction(void)
{
    return mock.applied_direction;
}

int8_t
linebot_port_mock_motion_get_correction(void)
{
    return mock.applied_correction;
}

int
linebot_port_mock_motion_verify_apply_calls(void)
{
    return mock.calls;
}