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
motion_update(core_vehicle_t *vehicle);

static void
state_indicator_update(core_vehicle_t *vehicle);

void
tasks_init(void)
{
    mq_init();
    core_port_motion_init();
    core_port_remote_control_init();
    core_port_state_indicator_init();
    core_port_coords_init();
}

void
tasks_run(core_vehicle_t *vehicle)
{
    remote_control_receive(vehicle);
    coords_receive(vehicle);
    mode_update(vehicle);
    motion_update(vehicle);
    state_indicator_update(vehicle);
}

static void
remote_control_receive(core_vehicle_t *vehicle)
{
    mq_message_t message;
    memset(&message, 0, sizeof(message));

    if (mq_pull(MQ_TOPIC_REMOTE_CONTROL, &message) == MQ_SUCCESS)
    {
        uint16_t raw_command = message.payload.command;
        uint16_t command     = core_port_remote_control_map(raw_command);

        core_vehicle_update_command(vehicle, command);
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

        core_vehicle_set_coords(vehicle, coords);
        core_vehicle_set_position_updated(vehicle, false);
    }
}

static void
mode_update(core_vehicle_t *vehicle)
{
    core_vehicle_update_state(vehicle);
}

static void
motion_update(core_vehicle_t *vehicle)
{
    if (core_vehicle_update_motion(vehicle) == CORE_VEHICLE_MOTION_CHANGED)
    {
        core_port_motion_apply(vehicle);
    }
}

static void
state_indicator_update(core_vehicle_t *vehicle)
{
    if (core_vehicle_is_state_changed(vehicle))
    {
        core_vehicle_state_t state = core_vehicle_get_state(vehicle);
        core_port_state_indicator_apply(state);
    }
}