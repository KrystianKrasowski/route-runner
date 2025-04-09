#include "mq.h"
#include <stdio.h>
#include <string.h>
#include <utils/queue.h>

#define QUEUE_TOPICS_SIZE 3

QUEUE_DECLARE(message, mq_message_t, MQ_SIZE)

static message_queue_t topics[QUEUE_TOPICS_SIZE];

mq_result_t
mq_init(void)
{
    for (uint8_t i = 0; i < QUEUE_TOPICS_SIZE; i++)
    {
        message_queue_init(&topics[i]);
    }

    return MQ_SUCCESS;
}

mq_result_t
mq_push(mq_topic_t const topic, mq_message_t *message)
{
    if (message_queue_push(&topics[topic], message) == QUEUE_SUCCESS)
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
    if (message_queue_pull(&topics[topic], message) == QUEUE_SUCCESS)
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
    message_queue_clear(&topics[topic]);
}

mq_message_t
mq_create_command_message(uint16_t command)
{
    mq_message_t message;
    message.type            = MQ_MESSAGE_TYPE_COMMAND;
    message.payload.command = command;

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