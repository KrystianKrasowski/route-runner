#include "core.h"
#include <queue.h>
#include <string.h>

static inline void
set_command_if_able(core_vehicle_t *vehicle, uint16_t command);

void
core_task_remote_control_receive(core_vehicle_t *vehicle)
{
    queue_message_t message;
    memset(&message, 0, sizeof(message));

    if (queue_pull(QUEUE_TOPIC_REMOTE_CONTROL, &message) == QUEUE_SUCCESS)
    {
        uint16_t raw_command = message.payload.command;
        uint16_t command     = core_port_remote_control_map(raw_command);
        
        set_command_if_able(vehicle, command);
    }
}

static inline void
set_command_if_able(core_vehicle_t *vehicle, uint16_t command)
{
    core_vehicle_state_t state = core_vehicle_get_state(vehicle);

    if (state == CORE_VEHICLE_STATE_LINE_FOLLOWING)
    {
        if (command & CORE_REMOTE_CONTROL_BREAK)
        {
            core_vehicle_set_command(vehicle, CORE_REMOTE_CONTROL_BREAK);
        }
        else if (command & CORE_REMOTE_CONTROL_NONE)
        {
            core_vehicle_set_command(vehicle, CORE_REMOTE_CONTROL_NONE);
        }
    }
    else 
    {
        core_vehicle_set_command(vehicle, command);
    }
}