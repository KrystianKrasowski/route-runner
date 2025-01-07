#include "core_interface_mock.h"

static bool           a_line_detected = false;
static core_control_t applied_control = {CORE_CONTROL_DIRECTION_STRIGHT, 0};
static core_command_t applied_command = CORE_COMMAND_NONE;
static core_state_t   applied_state   = CORE_VEHICLE_STATE_STANDBY;
static bool           stopped         = true;

bool
core_is_line_detected(void)
{
    return a_line_detected;
}

core_control_t
core_read_control(void)
{
    return applied_control;
}

core_command_t
core_read_command(void)
{
    return applied_command;
}

void
core_set_diagnostics(core_state_t state)
{
    applied_state = state;
}

void
core_run(core_control_t control)
{
    applied_control = control;
    stopped         = false;
}

void
core_stop(void)
{
    stopped = true;
}

void
core_mock_reset(void)
{
    a_line_detected           = false;
    applied_control.direction = CORE_CONTROL_DIRECTION_STRIGHT;
    applied_control.angle     = 0;
    applied_command           = CORE_COMMAND_NONE;
    applied_state             = CORE_VEHICLE_STATE_STANDBY;
    stopped                   = true;
}

void
core_mock_set_line_detected(bool is_detected)
{
    a_line_detected = is_detected;
}

void
core_mock_set_command(core_command_t command)
{
    applied_command = command;
}

void
core_mock_set_control(core_control_direction_t direction, uint8_t angle)
{
    applied_control.direction = direction;
    applied_control.angle     = angle;
}

core_control_t
core_mock_get_applied_control(void)
{
    return applied_control;
}

core_control_direction_t
core_mock_get_applied_control_direction(void)
{
    return applied_control.direction;
}

uint8_t
core_mock_get_applied_control_angle(void)
{
    return applied_control.angle;
}

core_command_t
core_mock_get_applied_command(void)
{
    return applied_command;
}

core_state_t
core_mock_get_applied_state(void)
{
    return applied_state;
}

bool
core_mock_is_stopped(void)
{
    return stopped;
}