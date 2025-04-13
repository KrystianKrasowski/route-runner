
#include "position.h"
#include "coords.h"
#include "position_regulator.h"
#include <string.h>
#include <utils/pool.h>
#include <utils/stack.h>

#define POSITION_POOL_SIZE 1

typedef struct
{
    linebot_coords_t coords;
    stack_t          errors;
} position_instance_t;

POOL_DECLARE(position, position_instance_t, 1)

static position_pool_t pool;

void
position_init(void)
{
    position_pool_init(&pool);
}

linebot_result_t
position_acquire(linebot_coords_t   coords,
                 uint8_t            errsize,
                 position_t * const handle)
{
    bool result = LINEBOT_ERR_POOL_EXCEEDED;

    if (position_pool_alloc(&pool, handle))
    {
        position_instance_t *position = position_pool_get(&pool, *handle);

        position->coords = coords;
        position->errors = stack(errsize);

        result = LINEBOT_OK;
    }

    return result;
}

void
position_release(position_t const self)
{
    position_instance_t *instance = position_pool_get(&pool, self);
    linebot_coords_release(instance->coords);
    position_pool_free(&pool, self);
}

void
position_update_coords(position_t const self, linebot_coords_t const coords)
{
    position_instance_t *instance = position_pool_get(&pool, self);
    coords_copy(instance->coords, coords);
}

bool
position_is_on_finish(position_t const self)
{
    position_instance_t *instance = position_pool_get(&pool, self);
    return coords_is_on_finish(instance->coords);
}

int8_t
position_last_error(position_t const self)
{
    int16_t              error    = 0;
    position_instance_t *instance = position_pool_get(&pool, self);
    stack_peek(&instance->errors, &error);

    return (int8_t)error;
}

int8_t
position_update_error(position_t const self)
{
    int8_t               error    = position_last_error(self);
    position_instance_t *instance = position_pool_get(&pool, self);

    coords_compute_mass_center(instance->coords, &error);
    stack_push_rolling(&instance->errors, error);

    return error;
}

int16_t
position_sum_errors(position_t const self)
{
    position_instance_t *instance = position_pool_get(&pool, self);
    int16_t              sum      = stack_sum(&instance->errors);

    return sum;
}

int8_t
position_regulate(position_t const self)
{
    return position_regulate_pid(self);
}