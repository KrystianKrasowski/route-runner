#include "motion.h"
#include <string.h>

#define MOTION_POOL_SIZE 3

typedef struct
{
    linebot_motion_direction_t direction;
    int8_t                     correction;
} motion_instance_t;

typedef struct
{
    motion_instance_t instances[MOTION_POOL_SIZE];
    bool              in_use[MOTION_POOL_SIZE];
} motion_pool_t;

static motion_pool_t pool;

void
motion_init(void)
{
    memset(&pool, 0, sizeof(pool));
}

linebot_result_t
motion_new_instance(linebot_motion_t * const handle)
{
    linebot_result_t result;
    uint8_t          index = MOTION_POOL_SIZE;

    for (uint8_t i = 0; i < MOTION_POOL_SIZE; i++)
    {
        if (false == pool.in_use[i])
        {
            index = i;
            break;
        }
    }

    if (index < MOTION_POOL_SIZE)
    {
        pool.in_use[index]               = true;
        pool.instances[index].correction = 0;
        pool.instances[index].direction  = LINEBOT_MOTION_NONE;

        *handle = index;
        result  = LINEBOT_SUCCESS;
    }
    else
    {
        result = LINEBOT_ERROR;
    }

    return result;
}

void
motion_release(linebot_motion_t const self)
{
    pool.in_use[self] = false;
}

void
motion_set_direction(linebot_motion_t const           self,
                     linebot_motion_direction_t const direction)
{
    pool.instances[self].direction = direction;
}

linebot_motion_direction_t
motion_get_direction(linebot_motion_t const self)
{
    return pool.instances[self].direction;
}

void
motion_set_correction(linebot_motion_t const self, int8_t const correction)
{
    pool.instances[self].correction = correction;
}

int8_t
motion_get_correction(linebot_motion_t const self)
{
    return pool.instances[self].correction;
}