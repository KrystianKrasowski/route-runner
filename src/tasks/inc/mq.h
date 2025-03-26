#ifndef _MQ_H
#define _MQ_H

#ifndef MQ_SIZE
#define MQ_SIZE 5
#endif

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    MQ_MESSAGE_TYPE_COMMAND,
    MQ_MESSAGE_TYPE_LINE_POSITION,
} mq_message_type_t;

typedef union mq_message_payload
{
    uint16_t command;
    uint8_t  line_position[6];
} mq_message_payload_t;

typedef struct mq_message
{
    mq_message_type_t    type;
    mq_message_payload_t payload;
} mq_message_t;

typedef enum
{
    MQ_TOPIC_REMOTE_CONTROL,
    MQ_TOPIC_LINE_POSITION,
} mq_topic_t;

typedef struct
{
    mq_message_t messages[MQ_SIZE];
    uint8_t      head;
    uint8_t      tail;
} mq_t;

typedef enum
{
    MQ_SUCCESS,
    MQ_FULL,
    MQ_EMPTY,
} mq_status_t;

mq_status_t
mq_push(mq_topic_t const topic, mq_message_t const message);

mq_status_t
mq_pull(mq_topic_t const topic, mq_message_t volatile *message);

void
mq_clear(mq_topic_t const topic);

uint8_t
mq_get_head(mq_topic_t const topic);

uint8_t
mq_get_tail(mq_topic_t const topic);

mq_message_t
mq_create_command_message(uint16_t command);

mq_message_t
mq_create_position_message(uint8_t position[]);

#endif