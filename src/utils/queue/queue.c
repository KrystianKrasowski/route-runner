#include "queue.h"
#include <stdio.h>

#define QUEUE_TOPICS_SIZE sizeof(queue_topic_t)

static volatile queue_t queues[QUEUE_TOPICS_SIZE] = {
    [QUEUE_TOPIC_REMOTE_CONTROLLER_COMMAND] = {
        .messages = {{0}},
        .head     = 0,
        .tail     = 0,
    }};

queue_status_t
queue_push(queue_topic_t const topic, queue_message_t const message)
{
    volatile queue_t *queue = &queues[topic];

    uint8_t next = (queue->head + 1) % QUEUE_SIZE;

    if (next == queue->tail)
    {
        return QUEUE_STATUS_MESSAGES_FULL;
    }

    queue->messages[queue->head] = message;
    queue->head                  = next;

    return QUEUE_STATUS_SUCCESS;
}

queue_status_t
queue_pull(queue_topic_t const topic, queue_message_t volatile *message)
{
    volatile queue_t *queue = &queues[topic];

    if (queue->head == queue->tail)
    {
        return QUEUE_STATUS_MESSAGES_EMPTY;
    }

    *message    = queue->messages[queue->tail];
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;

    return QUEUE_STATUS_SUCCESS;
}

void
queue_clear(queue_topic_t const topic)
{
    volatile queue_t *queue = &queues[topic];
    queue->head             = 0;
    queue->tail             = 0;
    queue_message_t blank   = {0};

    for (uint8_t i = 0; i < QUEUE_SIZE; i++)
    {
        queue->messages[i] = blank;
    }
}

uint8_t
queue_get_head(queue_topic_t const topic)
{
    volatile queue_t queue = queues[topic];
    return queue.head;
}

uint8_t
queue_get_tail(queue_topic_t const topic)
{
    volatile queue_t queue = queues[topic];
    return queue.tail;
}

queue_message_t
queue_message_create_command(int command)
{
    queue_message_t message = {.type    = QUEUE_MSG_TYPE_COMMAND,
                               .payload = {.command = command}};

    return message;
}