#include <pathbot/port.h>
#include <pathbot/port_mock_motion.h>

typedef struct
{
    int              apply_calls;
    pathbot_motion_t applied_motion;
} pathbot_port_mock_motion_t;

static pathbot_port_mock_motion_t mock;

void
pathbot_port_motion_apply(pathbot_motion_t const * const motion)
{
    mock.apply_calls++;
    mock.applied_motion = *motion;
}

void
pathbot_port_mock_motion_reset(void)
{
    pathbot_motion_t motion = {
        .correction = 0,
        .direction  = PATHBOT_DIRECTION_NONE,
    };

    mock.apply_calls    = 0;
    mock.applied_motion = motion;
}

int
pathbot_port_mock_motion_verify_apply_calls(void)
{
    return mock.apply_calls;
}

pathbot_motion_t
pathbot_port_mock_motion_get_applied(void)
{
    return mock.applied_motion;
}
