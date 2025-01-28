#ifndef _QUEUE_H
#define _QUEUE_H

#ifndef QUEUE_SIZE
#define QUEUE_SIZE 10
#endif

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    QUEUE_MSG_TYPE_COMMAND,
} queue_message_type_t;

typedef union queue_message_payload
{
    int command;
} queue_message_payload_t;

typedef struct queue_message
{
    queue_message_type_t    type;
    queue_message_payload_t payload;
} queue_message_t;

typedef enum
{
    QUEUE_TOPIC_REMOTE_CONTROLLER_COMMAND,
} queue_topic_t;

typedef struct
{
    queue_message_t messages[QUEUE_SIZE];
    uint8_t         head;
    uint8_t         tail;
} queue_t;

typedef enum
{
    QUEUE_STATUS_SUCCESS,
    QUEUE_STATUS_MESSAGES_FULL,
    QUEUE_STATUS_MESSAGES_EMPTY,
} queue_status_t;

queue_status_t
queue_push(queue_topic_t const topic, queue_message_t const message);

queue_status_t
queue_pull(queue_topic_t const topic, queue_message_t volatile *message);

void
queue_clear(queue_topic_t const topic);

uint8_t
queue_get_head(queue_topic_t const topic);

uint8_t
queue_get_tail(queue_topic_t const topic);

queue_message_t
queue_message_create_command(int command);

#endif