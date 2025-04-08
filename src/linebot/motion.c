#include "motion.h"
#include <string.h>
#include <utils/pool.h>

#define MOTION_POOL_SIZE 3

typedef struct
{
    linebot_motion_direction_t direction;
    int8_t                     correction;
} motion_instance_t;

POOL_DECLARE(motion, motion_instance_t, 3)

static motion_pool_t pool;

void
motion_init(void)
{
    motion_pool_init(&pool);
}

bool
motion_new(linebot_motion_direction_t direction,
           int8_t                     correction,
           linebot_motion_t * const   handle)
{
    bool result = false;

    if (motion_pool_alloc(&pool, handle))
    {
        motion_instance_t *motion = motion_pool_get(&pool, *handle);
        motion->direction = direction;
        motion->correction = correction;
        result = true;
    }

    return result;
}

void
motion_release(linebot_motion_t const self)
{
    motion_pool_free(&pool, self);
}

linebot_motion_direction_t
motion_get_direction(linebot_motion_t const self)
{
    motion_instance_t *motion = motion_pool_get(&pool, self);
    return motion->direction;
}

int8_t
motion_get_correction(linebot_motion_t const self)
{
    motion_instance_t *motion = motion_pool_get(&pool, self);
    return motion->correction;
}