#include <linebot/motion.h>
#include <string.h>
#include <utils/pool.h>

typedef struct
{
    linebot_motion_direction_t direction;
    int8_t                     correction;
} motion_instance_t;

POOL_DECLARE(motion, motion_instance_t, 1)

static motion_pool_t pool;
static bool          pool_initialized = false;

bool
linebot_motion_new(linebot_motion_direction_t const direction,
                   int8_t const                     correction,
                   linebot_motion_t * const         handle)
{
    bool result = false;

    if (!pool_initialized)
    {
        pool_initialized = true;
        motion_pool_init(&pool);
    }

    if (motion_pool_alloc(&pool, handle))
    {
        motion_instance_t *motion = motion_pool_get(&pool, *handle);
        motion->direction         = direction;
        motion->correction        = correction;
        result                    = true;
    }

    return result;
}

void
linebot_motion_free(linebot_motion_t const self)
{
    motion_pool_free(&pool, self);
}

linebot_motion_direction_t
linebot_motion_get_direction(linebot_motion_t const self)
{
    motion_instance_t const *motion = motion_pool_get(&pool, self);
    return motion->direction;
}

int8_t
linebot_motion_get_correction(linebot_motion_t const self)
{
    motion_instance_t const *motion = motion_pool_get(&pool, self);
    return motion->correction;
}