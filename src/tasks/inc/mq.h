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
    MQ_MESSAGE_TYPE_COORDS,
} mq_message_type_t;

typedef union mq_message_payload
{
    uint16_t command;
    uint8_t  coords[6];
} mq_message_payload_t;

typedef struct mq_message
{
    mq_message_type_t    type;
    mq_message_payload_t payload;
} mq_message_t;

typedef enum
{
    MQ_TOPIC_REMOTE_CONTROL,
    MQ_TOPIC_COORDS,
} mq_topic_t;

typedef enum
{
    MQ_SUCCESS,
    MQ_INIT_ERROR,
    MQ_FULL,
    MQ_EMPTY,
} mq_result_t;

mq_result_t
mq_init(void);

mq_result_t
mq_push(mq_topic_t const topic, mq_message_t message);

mq_result_t
mq_pull(mq_topic_t const topic, mq_message_t *message);

void
mq_clear(mq_topic_t const topic);

mq_message_t
mq_create_command_message(uint16_t command);

mq_message_t
mq_create_coords_message(uint8_t coords[]);

#endif