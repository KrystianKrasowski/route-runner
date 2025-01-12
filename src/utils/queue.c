#include "queue.h"
#include <stdio.h>

static volatile queue_t queue = {
    .messages = {0},
    .head     = 0,
    .tail     = 0,
};

bool
queue_push(queue_message_t const message)
{
    queue_lock();

    uint8_t next = (queue.head + 1) % QUEUE_SIZE;

    if (next == queue.tail)
    {
        return false;
    }

    queue.messages[queue.head] = message;
    queue.head                 = next;

    queue_unlock();

    return true;
}

volatile queue_message_t *
queue_pull()
{
    queue_lock();

    if (queue.head == queue.tail)
    {
        return NULL;
    }

    volatile queue_message_t *message = &queue.messages[queue.tail];
    queue.tail = (queue.tail + 1) % QUEUE_SIZE;

    queue_unlock();

    return message;
}

bool
queue_clear()
{
    queue.head            = 0;
    queue.tail            = 0;
    queue_message_t blank = {0};

    for (uint8_t i = 0; i < QUEUE_SIZE; i++)
    {
        queue.messages[i] = blank;
    }
}

uint8_t
queue_get_head()
{
    return queue.head;
}

uint8_t
queue_get_tail(void)
{
    return queue.tail;
}

__attribute__((weak)) void
queue_lock(void)
{
}

__attribute__((weak)) void
queue_unlock(void)
{
}

queue_message_t
queue_message_create_command(int command)
{
    queue_message_t message = {.type    = QUEUE_MSG_TYPE_COMMAND,
                               .payload = {.command = command}};

    return message;
}