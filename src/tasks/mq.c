#include "mq.h"
#include <stdio.h>
#include <string.h>
#include <utils/queue.h>

#define QUEUE_TOPICS_SIZE 2

static queue_t queues[QUEUE_TOPICS_SIZE];

mq_result_t
mq_init(void)
{
    for (uint8_t i = 0; i < QUEUE_TOPICS_SIZE; i++)
    {
        queue_result_t result =
            queue_init(&queues[i], MQ_SIZE, sizeof(mq_message_t));

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
mq_create_position_message(uint8_t position[])
{
    mq_message_t message;
    message.type = MQ_MESSAGE_TYPE_LINE_POSITION;

    memcpy(message.payload.line_position,
           position,
           sizeof(message.payload.line_position));

    return message;
}