#include "coords.h"
#include <errno.h>
#include <string.h>
#include <utils/pool.h>

#define COORDS_SIZE               6
#define COORDS_DETECTION_TRESHOLD 3

typedef struct
{
    uint8_t coordinates[COORDS_SIZE];
} coords_instance_t;

POOL_DECLARE(coords, coords_instance_t, 2)

static int8_t const COORDS_WEIGHTS[COORDS_SIZE] = {-100, -40, -20, 20, 40, 100};

static coords_pool_t pool;

int
linebot_coords_acquire(uint8_t const            l3,
                       uint8_t const            l2,
                       uint8_t const            l1,
                       uint8_t const            r1,
                       uint8_t const            r2,
                       uint8_t const            r3,
                       linebot_coords_t * const ph_self)
{
    int  result         = -ENOMEM;
    bool b_is_allocated = coords_pool_alloc(&pool, ph_self);

    if (b_is_allocated)
    {
        coords_instance_t *p_self = coords_pool_get(&pool, *ph_self);

        p_self->coordinates[0] = l3;
        p_self->coordinates[1] = l2;
        p_self->coordinates[2] = l1;
        p_self->coordinates[3] = r1;
        p_self->coordinates[4] = r2;
        p_self->coordinates[5] = r3;

        result = 0;
    }

    return result;
}

void
linebot_coords_release(linebot_coords_t const h_self)
{
    coords_pool_free(&pool, h_self);
}

void
coords_init(void)
{
    coords_pool_init(&pool);
}

int
coords_validate(linebot_coords_t const h_self)
{
    int result = 0;

    if (!coords_pool_get(&pool, h_self))
    {
        result = -EINVAL;
    }

    return result;
}

void
coords_copy(linebot_coords_t const h_self, linebot_coords_t const h_other)
{
    coords_instance_t       *p_self  = coords_pool_get(&pool, h_self);
    coords_instance_t const *p_other = coords_pool_get(&pool, h_other);

    memcpy(
        p_self->coordinates, p_other->coordinates, sizeof(p_self->coordinates));
}

bool
coords_is_on_route(linebot_coords_t const h_self)
{
    bool                     b_on_route = false;
    coords_instance_t const *p_self     = coords_pool_get(&pool, h_self);

    for (uint8_t i = 0; i < COORDS_SIZE; i++)
    {
        if (p_self->coordinates[i] >= COORDS_DETECTION_TRESHOLD)
        {
            b_on_route = true;
            break;
        }
    }

    return b_on_route;
}

bool
coords_is_on_finish(linebot_coords_t const h_self)
{
    bool                     b_on_finish = false;
    coords_instance_t const *p_self      = coords_pool_get(&pool, h_self);

    b_on_finish = p_self->coordinates[0] >= COORDS_DETECTION_TRESHOLD &&
                  p_self->coordinates[2] < COORDS_DETECTION_TRESHOLD &&
                  p_self->coordinates[3] < COORDS_DETECTION_TRESHOLD &&
                  p_self->coordinates[5] >= COORDS_DETECTION_TRESHOLD;

    return b_on_finish;
}

void
coords_compute_mass_center(linebot_coords_t const h_self, int8_t *p_value)
{
    coords_instance_t const *instance = coords_pool_get(&pool, h_self);

    int16_t sum        = 0;
    int16_t weight_sum = 0;

    for (uint8_t i = 0; i < COORDS_SIZE; i++)
    {
        sum += instance->coordinates[i];
        weight_sum += COORDS_WEIGHTS[i] * instance->coordinates[i];
    }

    if (sum != 0)
    {
        *p_value = weight_sum / sum;
    }
}