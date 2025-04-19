#ifndef _MQ_H
#define _MQ_H

#ifndef MQ_SIZE
#define MQ_SIZE 5
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define MQ_MAX_PAYLOAD_SIZE 6

typedef struct
{
    uint8_t payload[MQ_MAX_PAYLOAD_SIZE];
    size_t  size;
} mq_message_t;

typedef enum
{
    MQ_TOPIC_ROUTE_GUARD,
} mq_topic_t;

void
mq_init(void);

int
mq_push(mq_topic_t const topic, mq_message_t *p_message);

int
mq_pull(mq_topic_t const topic, mq_message_t *p_message);

void
mq_clear(mq_topic_t const topic);

mq_message_t
mq_create_message(void const *p_payload, size_t size);

#endif