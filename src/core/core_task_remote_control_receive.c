#include "core.h"
#include <queue.h>
#include <string.h>

void
core_task_remote_control_receive(core_vehicle_t *vehicle)
{
    queue_message_t message;
    memset(&message, 0, sizeof(message));

    if (queue_pull(QUEUE_TOPIC_REMOTE_CONTROL, &message) == QUEUE_SUCCESS)
    {
        uint16_t raw_command = message.payload.command;
        uint16_t command     = core_port_remote_control_map(raw_command);
        
        core_vehicle_apply_remote_control(vehicle, command);
    }
}