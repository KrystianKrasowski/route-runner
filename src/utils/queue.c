#include "utils/queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

queue_result_t
queue_init(queue_t volatile *self, uint8_t queue_size, size_t element_size)
{
    uint8_t capacity = queue_size + 1;

    if (capacity > QUEUE_MAX_CAPACITY)
    {
        return QUEUE_SIZE_TOO_LARGE;
    }

    if (element_size > QUEUE_ELEMENT_MAX_SIZE)
    {
        return QUEUE_ELEMENT_SIZE_TOO_LARGE;
    }

    for (uint8_t i = 0; i < capacity; i++)
    {
        for (uint8_t j = 0; j < element_size; j++)
        {
            self->elements[i][j] = 0;
        }
    }

    self->capacity     = capacity;
    self->element_size = element_size;
    self->head         = 0;
    self->tail         = 0;

    return QUEUE_SUCCESS;
}

queue_result_t
queue_push(queue_t volatile *self, void *element)
{
    uint8_t next = (self->tail + 1) % self->capacity;

    if (next == self->head)
    {
        return QUEUE_FULL;
    }

    uint8_t element_bytes[self->element_size];
    memcpy(&element_bytes, element, self->element_size);

    for (uint8_t i = 0; i < self->element_size; i++)
    {
        self->elements[self->tail][i] = element_bytes[i];
    }

    self->tail = next;

    return QUEUE_SUCCESS;
}

queue_result_t
queue_pull(queue_t volatile *self, void *element)
{
    if (self->head == self->tail)
    {
        return QUEUE_EMPTY;
    }

    uint8_t element_bytes[self->element_size];

    for (uint8_t i = 0; i < self->element_size; i++)
    {
        element_bytes[i] = self->elements[self->head][i];
    }

    memcpy(element, &element_bytes, self->element_size);
    self->head = (self->head + 1) % self->capacity;

    return QUEUE_SUCCESS;
}

void
queue_clear(queue_t volatile *self)
{
    queue_init(self, self->capacity, self->element_size);
}

uint8_t
queue_get_head(queue_t volatile *self)
{
    return self->head;
}

uint8_t
queue_get_tail(queue_t volatile *self)
{
    return self->tail;
}