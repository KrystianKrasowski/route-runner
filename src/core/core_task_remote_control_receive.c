#include "core_task.h"
#include "queue.h"
#include <string.h>

void
core_task_remote_control_receive(core_vehicle_t *vehicle)
{
    queue_message_t message;
    memset(&message, 0, sizeof(message));

    if (queue_pull(QUEUE_TOPIC_REMOTE_CONTROL, &message) == QUEUE_SUCCESS)
    {
        vehicle->command = message.payload.command;
    }
}