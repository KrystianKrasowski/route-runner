#include "core.h"
#include "core_interface.h"

static core_state_t vehicle_state = CORE_VEHICLE_STATE_STANDBY;

static core_state_t
core_state_update(core_command_t command);

static void
core_state_set_standby(core_command_t command);

static void
core_state_set_ready(void);

static void
core_state_set_running(core_command_t command);

static void
core_control_apply(core_control_t control);

void
core_execute(void)
{
    core_control_t control = core_read_control();
    core_command_t command = core_read_command();
    vehicle_state = core_state_update(command);
    core_control_apply(control);
    core_set_diagnostics(vehicle_state);
}

static core_state_t
core_state_update(core_command_t command)
{
    core_state_set_ready();
    core_state_set_running(command);
    core_state_set_standby(command);

    return vehicle_state;
}

static void
core_control_apply(core_control_t control)
{
    if (vehicle_state == CORE_VEHICLE_STATE_RUNNING)
    {
        core_run(control);
    }
    else
    {
        core_stop();
    }
}

static void
core_state_set_ready(void)
{
    if (vehicle_state == CORE_VEHICLE_STATE_STANDBY &&
        core_is_line_detected())
    {
        vehicle_state = CORE_VEHICLE_STATE_READY;
    }
}

static void
core_state_set_running(core_command_t command)
{
    if (vehicle_state == CORE_VEHICLE_STATE_READY &&
        core_is_line_detected() && command == CORE_COMMAND_RUN)
    {
        vehicle_state = CORE_VEHICLE_STATE_RUNNING;
    }
}

static void
core_state_set_standby(core_command_t command)
{
    if (command == CORE_COMMAND_RESET)
    {
        vehicle_state = CORE_VEHICLE_STATE_STANDBY;
    }
}