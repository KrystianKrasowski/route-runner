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

typedef struct
{
    queue_message_t messages[QUEUE_SIZE];
    uint8_t         head;
    uint8_t         tail;
    bool            locked;
} queue_t;

bool
queue_push(queue_message_t const message);

volatile queue_message_t *
queue_pull(void);

bool
queue_clear(void);

uint8_t
queue_get_head(void);

uint8_t
queue_get_tail(void);

void
queue_lock(void) __attribute__((weak));

void
queue_unlock(void) __attribute__((weak));

queue_message_t
queue_message_create_command(int command);

#endif