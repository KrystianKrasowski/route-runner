#include "context.h"
#include "position.h"
#include <errno.h>
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
context_init(void)
{
    linebot_pool_init(&pool);
}

int
context_acquire(linebot_mode_t    mode,
                linebot_coords_t  coords,
                uint8_t           errsize,
                linebot_t * const handle)
{
    int result = 0;

    if (linebot_pool_alloc(&pool, handle))
    {
        position_t position;

        // no need to verify result in module-private function
        (void)position_acquire(coords, errsize, &position);

        linebot_instance_t *instance = linebot_pool_get(&pool, *handle);

        instance->mode     = mode;
        instance->position = position;
    }
    else
    {
        result = -ENOMEM;
    }

    return result;
}

int
context_validate(linebot_t const self)
{
    int result = 0;

    if (!linebot_pool_get(&pool, self))
    {
        result = -EINVAL;
    }

    return result;
}

void
context_release(linebot_t const self)
{
    linebot_instance_t const *instance = linebot_pool_get(&pool, self);

    position_release(instance->position);
    linebot_pool_free(&pool, self);
}

linebot_mode_t
context_get_mode(linebot_t const self)
{
    linebot_instance_t const *instance = linebot_pool_get(&pool, self);

    return instance->mode;
}

position_t
context_get_position(linebot_t const self)
{
    linebot_instance_t const *instance = linebot_pool_get(&pool, self);

    return instance->position;
}

bool
context_update_mode(linebot_t const self, linebot_mode_t mode)
{
    bool                b_changed = false;
    linebot_instance_t *instance  = linebot_pool_get(&pool, self);

    if (instance->mode != mode)
    {
        instance->mode = mode;
        b_changed      = true;
    }

    return b_changed;
}

bool
context_is_tracking_route(linebot_t const self)
{
    linebot_mode_t mode = context_get_mode(self);

    return linebot_mode_is_tracking(mode);
}