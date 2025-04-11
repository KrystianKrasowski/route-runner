#include "linebot.h"
#include "coords.h"
#include "motion.h"
#include "position.h"
#include <linebot/api.h>
#include <utils/pool.h>

typedef struct
{
    linebot_mode_t mode;
    position_t     position;
} linebot_instance_t;

POOL_DECLARE(linebot, linebot_instance_t, 1)

static linebot_pool_t pool;

void
linebot_init(void)
{
    coords_init();
    position_init();
    motion_init();
    linebot_pool_init(&pool);
}

linebot_result_t
linebot_acquire(linebot_mode_t    mode,
                linebot_coords_t  coords,
                uint8_t           errsize,
                linebot_t * const handle)
{
    position_t       position;
    linebot_result_t result = position_acquire(coords, errsize, &position);

    if (linebot_pool_alloc(&pool, handle) && LINEBOT_OK == result)
    {
        linebot_instance_t *instance = linebot_pool_get(&pool, *handle);

        instance->mode     = mode;
        instance->position = position;
    }

    return result;
}

linebot_result_t
linebot_acquire_default(linebot_t * const handle)
{
    linebot_coords_t coords;
    linebot_result_t result = linebot_coords_acquire(0, 0, 0, 0, 0, 0, &coords);

    if (LINEBOT_OK == result)
    {
        result = linebot_acquire(LINEBOT_MODE_MANUAL, coords, 20, handle);
    }

    return result;
}

void
// cppcheck-suppress unusedFunction
linebot_release(linebot_t self)
{
    linebot_instance_t const *instance;

    if ((instance = linebot_pool_get(&pool, self)))
    {
        position_release(instance->position);
        linebot_pool_free(&pool, self);
    }
}

linebot_mode_t
linebot_get_mode(linebot_t const self)
{
    linebot_instance_t const *instance = linebot_pool_get(&pool, self);
    return instance->mode;
}

bool
linebot_update_mode(linebot_t const self, linebot_mode_t mode)
{
    bool                result   = false;
    linebot_instance_t *instance = linebot_pool_get(&pool, self);

    if (instance->mode != mode)
    {
        instance->mode = mode;
        result         = true;
    }

    return result;
}

linebot_result_t
linebot_get_position(linebot_t const self, position_t * const position)
{
    linebot_result_t          result = LINEBOT_OK;
    linebot_instance_t const *instance;

    if ((instance = linebot_pool_get(&pool, self)))
    {
        *position = instance->position;
    }
    else
    {
        result = LINEBOT_ERR_POOL_EXCEEDED;
    }

    return result;
}

bool
linebot_is_tracking_route(linebot_t const self)
{
    linebot_mode_t mode = linebot_get_mode(self);
    return linebot_mode_is_tracking(mode);
}