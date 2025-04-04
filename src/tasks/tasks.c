#include <core/ports.h>
#include <core/vehicle.h>
#include <mq.h>
#include <string.h>
#include <tasks.h>

static void
remote_control_receive(core_vehicle_t *vehicle);

static void
coords_receive(core_vehicle_t *vehicle);

static void
mode_update(core_vehicle_t *vehicle);

static void
route_guard_update(core_vehicle_t *vehicle);

static void
route_guard_timeout(core_vehicle_t *vehicle);

static void
motion_update(core_vehicle_t *vehicle);

static void
state_indicator_update(core_vehicle_t *vehicle);

static void
handle_control(core_vehicle_t *vehicle);

static void
handle_coordinates(core_vehicle_t *vehicle);

static void
handle_route_guard_timeout(core_vehicle_t *vehicle);

void
tasks_init(void)
{
    mq_init();
    core_port_motion_init();
    core_port_control_init();
    core_port_mode_indicator_init();
    core_port_coords_init();
    core_port_route_guard_init();
}

void
tasks_run(core_vehicle_t *vehicle)
{
    // remote_control_receive(vehicle);
    // coords_receive(vehicle);
    // mode_update(vehicle);
    // route_guard_update(vehicle);
    // route_guard_timeout(vehicle);
    // motion_update(vehicle);
    // state_indicator_update(vehicle);

    handle_control(vehicle);
    handle_coordinates(vehicle);
    handle_route_guard_timeout(vehicle);
}

static void
remote_control_receive(core_vehicle_t *vehicle)
{
    mq_message_t message;
    memset(&message, 0, sizeof(message));

    if (mq_pull(MQ_TOPIC_REMOTE_CONTROL, &message) == MQ_SUCCESS)
    {
        uint16_t raw_command = message.payload.command;
        uint16_t commands    = core_port_control_command_map(raw_command);

        core_vehicle_update_control(vehicle, core_control(commands));
    }
}

static void
coords_receive(core_vehicle_t *vehicle)
{
    mq_message_t message;

    if (mq_pull(MQ_TOPIC_COORDS, &message) == MQ_SUCCESS)
    {
        uint8_t      *raw_coords = message.payload.coords;
        core_coords_t coords     = core_port_coords_map(raw_coords);

        core_vehicle_update_coords(vehicle, coords);
    }
}

static void
mode_update(core_vehicle_t *vehicle)
{
    core_vehicle_update_mode(vehicle);
}

static void
route_guard_update(core_vehicle_t *vehicle)
{
    core_vehicle_update_route_guard(vehicle);
}

static void
route_guard_timeout(core_vehicle_t *vehicle)
{
    mq_message_t message;

    if (mq_pull(MQ_TOPIC_ROUTE_GUARD, &message) == MQ_SUCCESS)
    {
        core_vehicle_timeout_route_guard_old(vehicle);
    }
}

static void
motion_update(core_vehicle_t *vehicle)
{
    core_vehicle_update_motion(vehicle);
}

static void
state_indicator_update(core_vehicle_t *vehicle)
{
    core_vehicle_update_state_indicator(vehicle);
}

static void
handle_control(core_vehicle_t *vehicle)
{
    mq_message_t message;
    memset(&message, 0, sizeof(message));

    if (mq_pull(MQ_TOPIC_REMOTE_CONTROL, &message) == MQ_SUCCESS)
    {
        uint16_t       raw_command = message.payload.command;
        uint16_t       commands    = core_port_control_command_map(raw_command);
        core_control_t control     = core_control(commands);

        core_vehicle_change_mode_by_control(vehicle, control);
        core_vehicle_apply_manual_motion(vehicle, control);
    }
}

static void
handle_coordinates(core_vehicle_t *vehicle)
{
    mq_message_t message;
    memset(&message, 0, sizeof(message));

    if (mq_pull(MQ_TOPIC_COORDS, &message) == MQ_SUCCESS)
    {
        uint8_t      *raw_coords = message.payload.coords;
        core_coords_t coords     = core_port_coords_map(raw_coords);

        core_vehicle_change_mode_by_coords(vehicle, coords);
        core_vehicle_apply_following_motion(vehicle, coords);
    }
}

static void
handle_route_guard_timeout(core_vehicle_t *vehicle)
{
    mq_message_t message;

    if (mq_pull(MQ_TOPIC_ROUTE_GUARD, &message) == MQ_SUCCESS)
    {
        core_vehicle_timeout_route_guard(vehicle);
    }
}