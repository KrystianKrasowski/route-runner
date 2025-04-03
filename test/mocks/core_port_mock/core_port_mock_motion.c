#include "core_port_mock_motion.h"
#include <core/ports.h>
#include <stddef.h>

typedef struct
{
    core_motion_t *applied_motion;
    int            calls;
} mock_motion_t;

static mock_motion_t mock;

void
core_port_motion_apply(core_motion_t *motion)
{
    mock.applied_motion = motion;
    mock.calls++;
}

void
core_port_mock_motion_init(void)
{
    mock.applied_motion = NULL;
    mock.calls          = 0;
}

bool
core_port_motion_mock_verify_applied(void)
{
    return mock.calls > 0;
}

core_motion_t
core_port_motion_mock_get_applied(void)
{
    return *mock.applied_motion;
}

int
core_port_motion_mock_verify_apply_calls(void)
{
    return mock.calls;
}