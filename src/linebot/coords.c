#include "coords.h"
#include <errno.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

#define COORDS_MAX_SIZE           6
#define COORDS_DETECTION_TRESHOLD 3

typedef struct
{
    uint8_t coordinates[COORDS_MAX_SIZE];
    int8_t  weights[COORDS_MAX_SIZE];
    uint8_t size;
} coords_instance_t;

POOL_DECLARE(coords, coords_instance_t, 2)

static coords_pool_t pool;

static inline int
set_weights(int8_t weights[], uint8_t size);

int
linebot_coords_acquire(uint8_t const            coordinates[],
                       uint8_t const            size,
                       linebot_coords_t * const ph_self)
{
    if (!coords_pool_alloc(&pool, ph_self))
    {
        return -ENOMEM;
    }

    coords_instance_t *p_self = coords_pool_get(&pool, *ph_self);

    memcpy(p_self->coordinates, coordinates, size);
    set_weights(p_self->weights, size);
    p_self->size = size;

    return RESULT_OK;
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
    coords_instance_t const *p_self = coords_pool_get(&pool, h_self);

    for (uint8_t i = 0; i < COORDS_MAX_SIZE; i++)
    {
        if (p_self->coordinates[i] >= COORDS_DETECTION_TRESHOLD)
        {
            return true;
        }
    }

    return false;
}

bool
coords_is_on_finish(linebot_coords_t const h_self)
{
    coords_instance_t const *p_self = coords_pool_get(&pool, h_self);

    return p_self->coordinates[0] >= COORDS_DETECTION_TRESHOLD &&
           p_self->coordinates[2] < COORDS_DETECTION_TRESHOLD &&
           p_self->coordinates[3] < COORDS_DETECTION_TRESHOLD &&
           p_self->coordinates[5] >= COORDS_DETECTION_TRESHOLD;
}

void
coords_compute_mass_center(linebot_coords_t const h_self, int8_t *p_value)
{
    coords_instance_t const *p_self = coords_pool_get(&pool, h_self);

    int16_t sum        = 0;
    int16_t weight_sum = 0;

    for (uint8_t i = 0; i < COORDS_MAX_SIZE; i++)
    {
        sum += p_self->coordinates[i];
        weight_sum += p_self->weights[i] * p_self->coordinates[i];
    }

    if (sum != 0)
    {
        *p_value = weight_sum / sum;
    }
}

static inline int
set_weights(int8_t weights[], uint8_t size)
{
    int result = RESULT_OK;

    switch (size)
    {
        case 6:
            memcpy(weights, ((int8_t[]){-100, -40, -20, 20, 40, 100}), size);
            break;
        default:
            result = -EINVAL;
    }

    return result;
}