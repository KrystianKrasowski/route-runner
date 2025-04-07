#ifndef _POOL_H
#define _POOL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define POOL_DECLARE(name, type, size)                                         \
    typedef struct                                                             \
    {                                                                          \
        type objects[size];                                                    \
        bool used[size];                                                       \
    } name##_pool_t;                                                           \
                                                                               \
    static inline void name##_pool_init(name##_pool_t *pool)                   \
    {                                                                          \
        memset(pool, 0, sizeof(type));                                         \
    }                                                                          \
                                                                               \
    static inline bool name##_pool_alloc(name##_pool_t *pool, uint8_t *handle) \
    {                                                                          \
        for (uint8_t i = 0; i < size; i++)                                     \
        {                                                                      \
            if (!pool->used[i])                                                \
            {                                                                  \
                pool->used[i] = true;                                          \
                *handle       = i;                                             \
                                                                               \
                return true;                                                   \
            }                                                                  \
        }                                                                      \
                                                                               \
        return false;                                                          \
    }                                                                          \
                                                                               \
    static inline type *name##_pool_get(name##_pool_t *pool, uint8_t handle)   \
    {                                                                          \
        type *instance = NULL;                                                 \
                                                                               \
        if (handle < size && pool->used[handle])                               \
        {                                                                      \
            instance = &pool->objects[handle];                                 \
        }                                                                      \
                                                                               \
        return instance;                                                       \
    }                                                                          \
                                                                               \
    static inline void name##_pool_free(name##_pool_t *pool, uint8_t handle)  \
    {                                                                          \
        if (handle < size)                                                     \
        {                                                                      \
            pool->used[handle] = false;                                        \
        }                                                                      \
    }

#endif