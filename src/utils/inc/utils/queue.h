#ifndef _QUEUE_H
#define _QUEUE_H

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

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
    static inline int name##_queue_push(name##_queue_t *p_self,                \
                                        type const     *p_element)             \
    {                                                                          \
        int result = 0;                                                        \
                                                                               \
        uint8_t next = (p_self->tail + 1) % p_self->capacity;                  \
                                                                               \
        if (next == p_self->head)                                              \
        {                                                                      \
            result = -ENOBUFS;                                                 \
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
    static inline int name##_queue_pull(name##_queue_t *p_self,                \
                                        type           *p_element)             \
    {                                                                          \
        int result = 0;                                                        \
                                                                               \
        if (p_self->head == p_self->tail)                                      \
        {                                                                      \
            result = -ENODATA;                                                 \
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
    static inline bool name##_queue_empty(name##_queue_t const *p_self)        \
    {                                                                          \
        return p_self->head == p_self->tail;                                   \
    }                                                                          \
                                                                               \
    static inline void name##_queue_clear(name##_queue_t *p_self)              \
    {                                                                          \
        name##_queue_init(p_self);                                             \
    }

#endif
