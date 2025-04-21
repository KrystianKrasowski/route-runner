#include "motion.h"
#include <string.h>
#include <utils/pool.h>

typedef struct
{
    linebot_motion_direction_t direction;
    int8_t                     correction;
} motion_instance_t;

// cppcheck-suppress unusedFunction
POOL_DECLARE(motion, motion_instance_t, 1)

static motion_pool_t pool;

void
motion_init(void)
{
    motion_pool_init(&pool);
}

int
linebot_motion_acquire(linebot_motion_direction_t const direction,
                       int8_t const                     correction,
                       linebot_motion_t * const         ph_self)
{
    int  result      = 0;
    bool b_allocated = motion_pool_alloc(&pool, ph_self);

    if (b_allocated)
    {
        motion_instance_t *p_self = motion_pool_get(&pool, *ph_self);

        p_self->direction  = direction;
        p_self->correction = correction;

        result = true;
    }

    return result;
}

void
linebot_motion_release(linebot_motion_t const h_self)
{
    motion_pool_free(&pool, h_self);
}

linebot_motion_direction_t
linebot_motion_get_direction(linebot_motion_t const h_self)
{
    motion_instance_t const *p_self = motion_pool_get(&pool, h_self);
    return p_self->direction;
}

int8_t
linebot_motion_get_correction(linebot_motion_t const h_self)
{
    motion_instance_t const *p_self = motion_pool_get(&pool, h_self);
    return p_self->correction;
}