#include "mq.h"
#include <stdio.h>
#include <string.h>
#include <utils/queue.h>

#define QUEUE_TOPICS_SIZE 3

static queue_t queues[QUEUE_TOPICS_SIZE];

mq_result_t
mq_init(void)
{
    size_t queue_size = sizeof(mq_message_t);
    
    for (uint8_t i = 0; i < QUEUE_TOPICS_SIZE; i++)
    {
        queue_result_t result = queue_init(&queues[i], MQ_SIZE, queue_size);

        if (result != QUEUE_SUCCESS)
        {
            return MQ_INIT_ERROR;
        }
    }

    return MQ_SUCCESS;
}

mq_result_t
mq_push(mq_topic_t const topic, mq_message_t message)
{
    if (queue_push(&queues[topic], &message) == QUEUE_SUCCESS)
    {
        return MQ_SUCCESS;
    }
    else
    {
        return MQ_FULL;
    }
}

mq_result_t
mq_pull(mq_topic_t const topic, mq_message_t *message)
{
    if (queue_pull(&queues[topic], message) == QUEUE_SUCCESS)
    {
        return MQ_SUCCESS;
    }
    else
    {
        return MQ_EMPTY;
    }
}

void
mq_clear(mq_topic_t const topic)
{
    queue_clear(&queues[topic]);
}

mq_message_t
mq_create_command_message(uint16_t command)
{
    mq_message_t message = {.type    = MQ_MESSAGE_TYPE_COMMAND,
                            .payload = {.command = command}};

    return message;
}

mq_message_t
mq_create_coords_message(uint8_t coords[])
{
    mq_message_t message;
    message.type = MQ_MESSAGE_TYPE_COORDS;

    memcpy(message.payload.coords, coords, sizeof(message.payload.coords));

    return message;
}

mq_message_t
mq_create_route_guard_timeout_message(void)
{
    mq_message_t message;
    message.type = MQ_MESSAGE_TYPE_ROUTE_GUARD_TIMEOUT;

    return message;
}