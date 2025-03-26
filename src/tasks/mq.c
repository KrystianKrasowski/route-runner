#include "mq.h"
#include <stdio.h>
#include <string.h>

#define QUEUE_TOPICS_SIZE 2

static volatile mq_t queues[QUEUE_TOPICS_SIZE] = {
    [MQ_TOPIC_REMOTE_CONTROL] =
        {
            .messages = {{0}},
            .head     = 0,
            .tail     = 0,
        },
    [MQ_TOPIC_LINE_POSITION] = {
        .messages = {{0}},
        .head     = 0,
        .tail     = 0,
    }};

mq_status_t
mq_push(mq_topic_t const topic, mq_message_t const message)
{
    volatile mq_t *queue = &queues[topic];

    uint8_t next = (queue->head + 1) % MQ_SIZE;

    if (next == queue->tail)
    {
        return MQ_FULL;
    }

    queue->messages[queue->head] = message;
    queue->head                  = next;

    return MQ_SUCCESS;
}

mq_status_t
mq_pull(mq_topic_t const topic, mq_message_t volatile *message)
{
    volatile mq_t *queue = &queues[topic];

    if (queue->head == queue->tail)
    {
        return MQ_EMPTY;
    }

    *message    = queue->messages[queue->tail];
    queue->tail = (queue->tail + 1) % MQ_SIZE;

    return MQ_SUCCESS;
}

void
mq_clear(mq_topic_t const topic)
{
    volatile mq_t *queue = &queues[topic];
    queue->head             = 0;
    queue->tail             = 0;
    mq_message_t blank   = {0};

    for (uint8_t i = 0; i < MQ_SIZE; i++)
    {
        queue->messages[i] = blank;
    }
}

uint8_t
mq_get_head(mq_topic_t const topic)
{
    volatile mq_t queue = queues[topic];
    return queue.head;
}

uint8_t
mq_get_tail(mq_topic_t const topic)
{
    volatile mq_t queue = queues[topic];
    return queue.tail;
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