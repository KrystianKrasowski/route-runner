#include "core_port_mock.h"
#include <core_port.h>
#include <string.h>

static core_motion_t motion_applied;
static bool          is_motion_applied = false;

uint16_t
core_port_remote_control_map(uint16_t raw_command)
{
    return raw_command;
}

void
core_port_motion_apply(core_motion_t *motion)
{
    motion_applied    = *motion;
    is_motion_applied = true;
}

void
core_port_mock_reset(void)
{
    memset(&motion_applied, 0, sizeof(motion_applied));
}

bool
core_port_mock_verify_motion_applied(void)
{
    return is_motion_applied;
}

core_motion_t
core_port_mock_get_motion_applied(void)
{
    return motion_applied;
}