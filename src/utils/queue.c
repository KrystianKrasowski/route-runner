#include "utils/queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

queue_result_t
queue_init(queue_t *self, uint8_t queue_size, size_t element_size)
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

    memset(self->elements, 0, capacity);

    self->capacity     = capacity;
    self->element_size = element_size;
    self->head         = 0;
    self->tail         = 0;

    return QUEUE_SUCCESS;
}

queue_result_t
queue_push(queue_t *self, void *element)
{
    uint8_t next = (self->tail + 1) % self->capacity;

    if (next == self->head)
    {
        return QUEUE_FULL;
    }

    memcpy(self->elements[self->tail], element, self->element_size);

    self->tail = next;

    return QUEUE_SUCCESS;
}

queue_result_t
queue_pull(queue_t *self, void *element)
{
    if (self->head == self->tail)
    {
        return QUEUE_EMPTY;
    }

    memcpy(element, self->elements[self->head], self->element_size);
    self->head = (self->head + 1) % self->capacity;

    return QUEUE_SUCCESS;
}

void
queue_clear(queue_t *self)
{
    queue_init(self, self->capacity, self->element_size);
}

uint8_t
queue_get_head(queue_t *self)
{
    return self->head;
}

uint8_t
queue_get_tail(queue_t *self)
{
    return self->tail;
}