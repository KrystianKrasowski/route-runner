#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define QUEUE_MAX_SIZE 5

typedef struct queue
{
    uint16_t elements[QUEUE_MAX_SIZE];
    uint8_t  queue_size;
    size_t   element_size;
    uint8_t  head;
    uint8_t  tail;
} queue_t;

typedef enum
{
    QUEUE_SUCCESS,
    QUEUE_SIZE_TOO_LARGE,
    QUEUE_FULL,
    QUEUE_EMPTY,
} queue_result_t;

queue_result_t
queue_init(queue_t *self, uint8_t queue_size, size_t element_size);

queue_result_t
queue_push(queue_t *self, void *element);

queue_result_t
queue_pull(queue_t *self, void *element);

void
queue_clear(queue_t *self);

uint8_t
queue_get_head(queue_t *self);

uint8_t
queue_get_tail(queue_t *self);

#endif