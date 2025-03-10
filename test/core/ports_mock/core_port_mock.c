#include "core_port_mock.h"
#include <string.h>

static core_motion_t motion_applied;
static bool          is_motion_applied = false;

static core_vehicle_state_t state_indicator;
static bool                 is_state_indicator_updated = false;

uint16_t
core_port_remote_control_map(uint16_t raw_command)
{
    return raw_command;
}

void
core_port_motion_apply(core_vehicle_t *vehicle)
{
    motion_applied    = vehicle->motion;
    is_motion_applied = true;
}

void
core_port_state_indicator_apply(core_vehicle_state_t state)
{
    state_indicator            = state;
    is_state_indicator_updated = true;
}

core_position_t
core_port_line_position_map(uint8_t *raw_position)
{
    core_position_t position;
    position.left_3  = raw_position[0];
    position.left_2  = raw_position[1];
    position.left_1  = raw_position[2];
    position.right_1 = raw_position[3];
    position.right_2 = raw_position[4];
    position.right_3 = raw_position[5];

    return position;
}

void
core_port_mock_reset(void)
{
    memset(&motion_applied, 0, sizeof(motion_applied));
    is_motion_applied          = false;
    is_state_indicator_updated = false;
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

core_vehicle_state_t
core_port_mock_get_state_indicator_applied(void)
{
    return state_indicator;
}

bool
core_port_mock_verify_state_indicator_updated(void)
{
    return is_state_indicator_updated;
}