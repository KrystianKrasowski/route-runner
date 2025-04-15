
#include "position.h"
#include "coords.h"
#include "position_regulator.h"
#include <errno.h>
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

int
position_acquire(linebot_coords_t   coords,
                 uint8_t            errsize,
                 position_t * const ph_self)
{
    int result = -ENOMEM;

    if (position_pool_alloc(&pool, ph_self))
    {
        position_instance_t *p_self = position_pool_get(&pool, *ph_self);

        p_self->coords = coords;
        p_self->errors = stack(errsize);

        result = 0;
    }

    return result;
}

void
position_release(position_t const h_self)
{
    position_instance_t *p_self = position_pool_get(&pool, h_self);
    linebot_coords_release(p_self->coords);
    position_pool_free(&pool, h_self);
}

void
position_update_coords(position_t const h_self, linebot_coords_t const h_coords)
{
    position_instance_t *p_self = position_pool_get(&pool, h_self);
    coords_copy(p_self->coords, h_coords);
}

bool
position_is_on_finish(position_t const h_self)
{
    position_instance_t *p_self = position_pool_get(&pool, h_self);
    return coords_is_on_finish(p_self->coords);
}

int8_t
position_last_error(position_t const h_self)
{
    int16_t              error  = 0;
    position_instance_t *p_self = position_pool_get(&pool, h_self);
    stack_peek(&p_self->errors, &error);

    return (int8_t)error;
}

int8_t
position_update_error(position_t const h_self)
{
    int8_t               error  = position_last_error(h_self);
    position_instance_t *p_self = position_pool_get(&pool, h_self);

    coords_compute_mass_center(p_self->coords, &error);
    stack_push_rolling(&p_self->errors, error);

    return error;
}

int16_t
position_sum_errors(position_t const h_self)
{
    position_instance_t *p_self = position_pool_get(&pool, h_self);
    int16_t              sum    = stack_sum(&p_self->errors);

    return sum;
}

int8_t
position_regulate(position_t const h_self)
{
    return position_regulate_pid(h_self);
}