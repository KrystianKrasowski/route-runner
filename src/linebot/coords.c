#include "coords.h"
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
static bool          pool_initialized;

bool
linebot_new_coords(uint8_t const            l3,
                   uint8_t const            l2,
                   uint8_t const            l1,
                   uint8_t const            r1,
                   uint8_t const            r2,
                   uint8_t const            r3,
                   linebot_coords_t * const handle)
{
    bool result = false;

    if (!pool_initialized)
    {
        pool_initialized = true;
        coords_pool_init(&pool);
    }

    if (coords_pool_alloc(&pool, handle))
    {
        coords_instance_t *coords = coords_pool_get(&pool, *handle);

        if (coords)
        {
            coords->coordinates[0] = l3;
            coords->coordinates[1] = l2;
            coords->coordinates[2] = l1;
            coords->coordinates[3] = r1;
            coords->coordinates[4] = r2;
            coords->coordinates[5] = r3;
            result                 = true;
        }
    }

    return result;
}

void
linebot_free_coords(linebot_coords_t const self)
{
    coords_pool_free(&pool, self);
}

void
coords_copy(linebot_coords_t const self, linebot_coords_t const other)
{
    coords_instance_t       *instance_self  = coords_pool_get(&pool, self);
    coords_instance_t const *instance_other = coords_pool_get(&pool, other);

    if (instance_self && instance_other)
    {
        memcpy(instance_self->coordinates,
               instance_other->coordinates,
               sizeof(instance_self->coordinates));
    }
}

bool
coords_is_on_route(linebot_coords_t const self)
{
    bool                     on_route = false;
    coords_instance_t const *instance;

    if ((instance = coords_pool_get(&pool, self)))
    {
        for (uint8_t i = 0; i < COORDS_SIZE; i++)
        {
            if (instance->coordinates[i] >= COORDS_DETECTION_TRESHOLD)
            {
                on_route = true;
                break;
            }
        }
    }

    return on_route;
}

bool
coords_is_on_finish(linebot_coords_t const self)
{
    bool                     on_finish = false;
    coords_instance_t const *instance  = coords_pool_get(&pool, self);

    if (instance)
    {
        on_finish = instance->coordinates[0] >= COORDS_DETECTION_TRESHOLD &&
                    instance->coordinates[2] < COORDS_DETECTION_TRESHOLD &&
                    instance->coordinates[3] < COORDS_DETECTION_TRESHOLD &&
                    instance->coordinates[5] >= COORDS_DETECTION_TRESHOLD;
    }

    return on_finish;
}

void
coords_compute_mass_center(linebot_coords_t const self, int8_t *value)
{
    coords_instance_t const *instance;

    if ((instance = coords_pool_get(&pool, self)))
    {
        int16_t sum        = 0;
        int16_t weight_sum = 0;

        for (uint8_t i = 0; i < COORDS_SIZE; i++)
        {
            sum += instance->coordinates[i];
            weight_sum += COORDS_WEIGHTS[i] * instance->coordinates[i];
        }

        if (sum != 0)
        {
            *value = weight_sum / sum;
        }
    }
}