#include "core.h"
#include <queue.h>

void
core_task_line_position_receive(core_vehicle_t *vehicle)
{
    queue_message_t message;

    if (queue_pull(QUEUE_TOPIC_LINE_POSITION, &message) == QUEUE_SUCCESS)
    {
        uint8_t        *raw_position = message.payload.line_position;
        core_position_t position = core_port_line_position_map(raw_position);

        core_vehicle_set_line_position(vehicle, position);
    }
}