#include "core_port_mock.h"
#include <string.h>

static core_motion_t motion_applied;
static int           motion_applied_count = 0;
static bool          is_motion_applied    = false;

struct state_indicator_mock
{
    int calls;
};

static struct state_indicator_mock state_indicator;

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
    motion_applied_count++;
}

void
core_port_mode_indicator_apply(core_mode_value_t value)
{
    state_indicator.calls++;
}

core_coords_t
core_port_coords_map(uint8_t *raw)
{
    core_coords_t coords;
    core_coords_init(&coords);

    for (uint8_t i = 0; i < CORE_COORDS_SIZE; i++)
    {
        core_coords_set_place(&coords, i, raw[i]);
    }

    return coords;
}

void
core_port_mock_reset(void)
{
    memset(&motion_applied, 0, sizeof(motion_applied));
    is_motion_applied     = false;
    motion_applied_count  = 0;
    state_indicator.calls = 0;
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

int
core_port_mock_verify_motion_apply_calls(void)
{
    return motion_applied_count;
}

int
core_port_mock_verify_state_indicator_apply_calls(void)
{
    return state_indicator.calls;
}