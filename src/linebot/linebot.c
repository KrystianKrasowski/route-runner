#include "linebot.h"
#include <linebot/api.h>
#include <utils/pool.h>

typedef struct
{
    linebot_mode_t mode;
    position_t     position;
} linebot_instance_t;

POOL_DECLARE(linebot, linebot_instance_t, 1)

static linebot_pool_t pool;
static bool           pool_initialized = false;

void
linebot_init(void)
{
    // TODO implement library initialization:
    //  - init object pools
    //  - instantiate linebot context
}

bool
linebot_new(linebot_mode_t    mode,
            linebot_coords_t  coords,
            uint8_t           errsize,
            linebot_t * const handle)
{
    bool       linebot_created = false;
    position_t position;
    bool       position_created = position_new(coords, errsize, &position);

    if (!pool_initialized)
    {
        pool_initialized = true;
        linebot_pool_init(&pool);
    }

    if (linebot_pool_alloc(&pool, handle) && position_created)
    {
        linebot_instance_t *instance = linebot_pool_get(&pool, *handle);
        instance->mode               = mode;
        instance->position           = position;
        linebot_created              = true;
    }

    return linebot_created;
}

void
// cppcheck-suppress unusedFunction
linebot_free(linebot_t self)
{
    linebot_instance_t const *instance;

    if ((instance = linebot_pool_get(&pool, self)))
    {
        position_free(instance->position);
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
        result = LINEBOT_ERROR_OBJECT_POOL;
    }

    return result;
}

bool
linebot_is_tracking_route(linebot_t const self)
{
    linebot_mode_t mode = linebot_get_mode(self);
    return linebot_mode_is_tracking(mode);
}