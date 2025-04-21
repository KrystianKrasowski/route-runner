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

// cppcheck-suppress unusedFunction
POOL_DECLARE(linebot, linebot_instance_t, 1)

static linebot_pool_t pool;

void
context_init(void)
{
    linebot_pool_init(&pool);
}

int
context_acquire(linebot_mode_t    mode,
                linebot_coords_t  h_coords,
                uint8_t           errsize,
                linebot_t * const ph_self)
{
    int result = 0;

    if (linebot_pool_alloc(&pool, ph_self))
    {
        position_t h_position;

        // no need to verify result in module-private function
        (void)position_acquire(h_coords, errsize, &h_position);

        linebot_instance_t *p_self = linebot_pool_get(&pool, *ph_self);

        p_self->mode     = mode;
        p_self->position = h_position;
    }
    else
    {
        result = -ENOMEM;
    }

    return result;
}

int
context_validate(linebot_t const h_self)
{
    int result = 0;

    if (!linebot_pool_get(&pool, h_self))
    {
        result = -EINVAL;
    }

    return result;
}

void
context_release(linebot_t const h_self)
{
    linebot_instance_t const *p_self = linebot_pool_get(&pool, h_self);

    position_release(p_self->position);
    linebot_pool_free(&pool, h_self);
}

linebot_mode_t
context_get_mode(linebot_t const h_self)
{
    linebot_instance_t const *p_self = linebot_pool_get(&pool, h_self);

    return p_self->mode;
}

position_t
context_get_position(linebot_t const h_self)
{
    linebot_instance_t const *p_self = linebot_pool_get(&pool, h_self);

    return p_self->position;
}

bool
context_update_mode(linebot_t const h_self, linebot_mode_t const mode)
{
    bool                b_changed = false;
    linebot_instance_t *p_self    = linebot_pool_get(&pool, h_self);

    if (p_self->mode != mode)
    {
        p_self->mode = mode;
        b_changed    = true;
    }

    return b_changed;
}

bool
context_is_tracking_route(linebot_t const h_self)
{
    linebot_mode_t mode = context_get_mode(h_self);

    return linebot_mode_is_tracking(mode);
}