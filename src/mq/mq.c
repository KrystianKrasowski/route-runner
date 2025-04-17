#include <mq.h>
#include <stdio.h>
#include <string.h>
#include <utils/queue.h>

#define QUEUE_TOPICS_SIZE 3

QUEUE_DECLARE(message, mq_message_t, MQ_SIZE)

static message_queue_t topics[QUEUE_TOPICS_SIZE];

void
mq_init(void)
{
    for (uint8_t i = 0; i < QUEUE_TOPICS_SIZE; i++)
    {
        message_queue_init(&topics[i]);
    }
}

int
mq_push(mq_topic_t const topic, mq_message_t *p_message)
{
    return message_queue_push(&topics[topic], p_message);
}

int
mq_pull(mq_topic_t const topic, mq_message_t *p_message)
{
    return message_queue_pull(&topics[topic], p_message);
}

void
// cppcheck-suppress unusedFunction
mq_clear(mq_topic_t const topic)
{
    message_queue_clear(&topics[topic]);
}

mq_message_t
mq_create_message(void const *p_payload, size_t size)
{
    mq_message_t message;
    memcpy(&message.payload, p_payload, size);
    message.size = size;

    return message;
}

