#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdint.h>
#include <string.h>

typedef enum
{
    QUEUE_SUCCESS,
    QUEUE_SIZE_TOO_LARGE,
    QUEUE_ELEMENT_SIZE_TOO_LARGE,
    QUEUE_FULL,
    QUEUE_EMPTY,
} queue_result_t;

#define QUEUE_DECLARE(name, type, size)                                        \
    typedef struct                                                             \
    {                                                                          \
        type    elements[size + 1];                                            \
        uint8_t capacity;                                                      \
        uint8_t head;                                                          \
        uint8_t tail;                                                          \
    } name##_queue_t;                                                          \
                                                                               \
    static inline void name##_queue_init(name##_queue_t *self)                 \
    {                                                                          \
        memset(self->elements, 0, sizeof(self->elements));                     \
        self->capacity = size + 1;                                             \
        self->head     = 0;                                                    \
        self->tail     = 0;                                                    \
    }                                                                          \
                                                                               \
    static inline queue_result_t name##_queue_push(name##_queue_t *self,       \
                                                   type           *element)    \
    {                                                                          \
        queue_result_t result = QUEUE_SUCCESS;                                 \
                                                                               \
        uint8_t next = (self->tail + 1) % self->capacity;                      \
                                                                               \
        if (next == self->head)                                                \
        {                                                                      \
            result = QUEUE_FULL;                                               \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            self->elements[self->tail] = *element;                             \
            self->tail                 = next;                                 \
        }                                                                      \
                                                                               \
        return result;                                                         \
    }                                                                          \
                                                                               \
    static inline queue_result_t name##_queue_pull(name##_queue_t *self,       \
                                                   type           *element)    \
    {                                                                          \
        queue_result_t result = QUEUE_SUCCESS;                                 \
                                                                               \
        if (self->head == self->tail)                                          \
        {                                                                      \
            result = QUEUE_EMPTY;                                              \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            *element   = self->elements[self->head];                           \
            self->head = (self->head + 1) % self->capacity;                    \
        }                                                                      \
                                                                               \
        return result;                                                         \
    }                                                                          \
                                                                               \
    static inline void name##_queue_clear(name##_queue_t *self)                \
    {                                                                          \
        name##_queue_init(self);                                               \
    }

#endif