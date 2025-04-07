#include "position.h"
#include "coords.h"
#include "position_regulator.h"
#include <string.h>

#define POSITION_POOL_SIZE 1

typedef struct
{
    linebot_coords_t coords;
    stack_t          errors;
} position_instance_t;

typedef struct
{
    position_instance_t instances[POSITION_POOL_SIZE];
    bool                in_use[POSITION_POOL_SIZE];
} position_pool_t;

static position_pool_t pool;

void
position_init(void)
{
    memset(&pool, 0, sizeof(pool));
}

linebot_result_t
position_new_instance(position_t * const handle)
{
    linebot_result_t result;
    uint8_t          index = POSITION_POOL_SIZE;
    linebot_coords_t coords;

    for (uint8_t i = 0; i < POSITION_POOL_SIZE; i++)
    {
        if (false == pool.in_use[i])
        {
            index = i;
            break;
        }
    }

    bool pool_full = index == POSITION_POOL_SIZE;
    bool coords_created =
        coords_new(0, 0, 0, 0, 0, 0, &coords) == LINEBOT_SUCCESS;

    if (!pool_full && coords_created)
    {
        pool.in_use[index]           = true;
        pool.instances[index].coords = coords;
        pool.instances[index].errors = stack(20);
        *handle                      = index;
        result                       = LINEBOT_SUCCESS;
    }
    else
    {
        result = LINEBOT_ERROR;
    }

    return result;
}

void
position_update_coords(position_t const self, linebot_coords_t const coords)
{
    coords_copy(pool.instances[self].coords, coords);
}

int8_t
position_last_error(position_t const self)
{
    int16_t error = 0;
    stack_peek(&pool.instances[self].errors, &error);

    return (int8_t)error;
}

int8_t
position_update_error(position_t const self)
{
    int8_t error = position_last_error(self);
    coords_compute_mass_center(pool.instances[self].coords, &error);
    stack_push_rolling(&pool.instances[self].errors, error);

    return error;
}

int16_t
position_sum_errors(position_t const self)
{
    return stack_sum(&pool.instances[self].errors);
}

int8_t
position_regulate(position_t const self)
{
    return position_regulate_pid(self);
}