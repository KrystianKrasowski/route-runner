#ifndef _POOL_H
#define _POOL_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define POOL_DECLARE(name, type, size)                                         \
    typedef struct                                                             \
    {                                                                          \
        type objects[size];                                                    \
        bool used[size];                                                       \
    } name##_pool_t;                                                           \
                                                                               \
    static inline void name##_pool_init(name##_pool_t *p_pool)                 \
    {                                                                          \
        memset(p_pool, 0, sizeof(*p_pool));                                    \
    }                                                                          \
                                                                               \
    static inline bool name##_pool_alloc(name##_pool_t *p_pool,                \
                                         uint8_t       *ph_obj)                \
    {                                                                          \
        for (uint8_t i = 0; i < size; i++)                                     \
        {                                                                      \
            if (!p_pool->used[i])                                              \
            {                                                                  \
                p_pool->used[i] = true;                                        \
                *ph_obj         = i;                                           \
                                                                               \
                return true;                                                   \
            }                                                                  \
        }                                                                      \
                                                                               \
        return false;                                                          \
    }                                                                          \
                                                                               \
    static inline bool name##_pool_alloc_at(name##_pool_t *p_pool,             \
                                            uint8_t        ind)                \
    {                                                                          \
        if (ind < size)                                                        \
        {                                                                      \
            p_pool->used[ind] = true;                                          \
            return true;                                                       \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            return false;                                                      \
        }                                                                      \
    }                                                                          \
                                                                               \
    static inline type *name##_pool_get(name##_pool_t *p_pool, uint8_t h_obj)  \
    {                                                                          \
        type *instance = NULL;                                                 \
                                                                               \
        if (h_obj < size && p_pool->used[h_obj])                               \
        {                                                                      \
            instance = &p_pool->objects[h_obj];                                \
        }                                                                      \
                                                                               \
        return instance;                                                       \
    }                                                                          \
                                                                               \
    static inline void name##_pool_free(name##_pool_t *p_pool, uint8_t h_obj)  \
    {                                                                          \
        if (h_obj < size)                                                      \
        {                                                                      \
            p_pool->used[h_obj] = false;                                       \
        }                                                                      \
    }

#endif
