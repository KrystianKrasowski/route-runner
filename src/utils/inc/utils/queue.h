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
    static inline void name##_queue_init(name##_queue_t *p_self)               \
    {                                                                          \
        memset(p_self->elements, 0, sizeof(p_self->elements));                 \
        p_self->capacity = size + 1;                                           \
        p_self->head     = 0;                                                  \
        p_self->tail     = 0;                                                  \
    }                                                                          \
                                                                               \
    static inline queue_result_t name##_queue_push(name##_queue_t *p_self,     \
                                                   type           *p_element)  \
    {                                                                          \
        queue_result_t result = QUEUE_SUCCESS;                                 \
                                                                               \
        uint8_t next = (p_self->tail + 1) % p_self->capacity;                  \
                                                                               \
        if (next == p_self->head)                                              \
        {                                                                      \
            result = QUEUE_FULL;                                               \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            p_self->elements[p_self->tail] = *p_element;                       \
            p_self->tail                   = next;                             \
        }                                                                      \
                                                                               \
        return result;                                                         \
    }                                                                          \
                                                                               \
    static inline queue_result_t name##_queue_pull(name##_queue_t *p_self,     \
                                                   type           *p_element)  \
    {                                                                          \
        queue_result_t result = QUEUE_SUCCESS;                                 \
                                                                               \
        if (p_self->head == p_self->tail)                                      \
        {                                                                      \
            result = QUEUE_EMPTY;                                              \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            *p_element   = p_self->elements[p_self->head];                     \
            p_self->head = (p_self->head + 1) % p_self->capacity;              \
        }                                                                      \
                                                                               \
        return result;                                                         \
    }                                                                          \
                                                                               \
    static inline void name##_queue_clear(name##_queue_t *p_self)              \
    {                                                                          \
        name##_queue_init(p_self);                                             \
    }

#endif