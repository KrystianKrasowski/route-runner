#include "coords.h"
#include <string.h>

#define COORDS_POOL_SIZE          2
#define COORDS_SIZE               6
#define COORDS_DETECTION_TRESHOLD 3

typedef struct
{
    uint8_t coordinates[COORDS_SIZE];
} coords_instance_t;

typedef struct
{
    coords_instance_t instances[COORDS_POOL_SIZE];
    bool              in_use[COORDS_POOL_SIZE];
} coords_pool_t;

static int8_t const coords_weights[COORDS_SIZE] = {-100, -40, -20, 20, 40, 100};

static coords_pool_t pool;

void
coords_init(void)
{
    memset(&pool, 0, sizeof(pool));
}

linebot_result_t
coords_new(uint8_t const            l3,
           uint8_t const            l2,
           uint8_t const            l1,
           uint8_t const            r1,
           uint8_t const            r2,
           uint8_t const            r3,
           linebot_coords_t * const handle)
{
    linebot_result_t result;
    uint8_t          index = COORDS_POOL_SIZE;

    for (uint8_t i = 0; i < COORDS_POOL_SIZE; i++)
    {
        if (false == pool.in_use[i])
        {
            index = i;
            break;
        }
    }

    if (index < COORDS_POOL_SIZE)
    {
        pool.in_use[index]                   = true;
        pool.instances[index].coordinates[0] = l3;
        pool.instances[index].coordinates[1] = l2;
        pool.instances[index].coordinates[2] = l1;
        pool.instances[index].coordinates[3] = r1;
        pool.instances[index].coordinates[4] = r2;
        pool.instances[index].coordinates[5] = r3;

        *handle = index;
        result  = LINEBOT_SUCCESS;
    }
    else
    {
        result = LINEBOT_ERROR;
    }

    return result;
}

void
coords_release(linebot_coords_t const self)
{
    pool.in_use[self] = false;
}

void
coords_copy(linebot_coords_t const self, linebot_coords_t const other)
{
    memcpy(pool.instances[self].coordinates,
           pool.instances[other].coordinates,
           sizeof(pool.instances[self].coordinates));
}

bool
coords_is_on_route(linebot_coords_t const self)
{
    for (uint8_t i = 0; i < COORDS_POOL_SIZE; i++)
    {
        if (pool.instances[self].coordinates[i] >= COORDS_DETECTION_TRESHOLD)
        {
            return true;
        }
    }

    return false;
}

bool
coords_is_on_finish(linebot_coords_t const self)
{
    coords_instance_t instance = pool.instances[self];

    return instance.coordinates[0] >= COORDS_DETECTION_TRESHOLD &&
           instance.coordinates[2] < COORDS_DETECTION_TRESHOLD &&
           instance.coordinates[3] < COORDS_DETECTION_TRESHOLD &&
           instance.coordinates[5] >= COORDS_DETECTION_TRESHOLD;
}

void
coords_compute_mass_center(linebot_coords_t const self, int8_t *value)
{
    int16_t           sum        = 0;
    int16_t           weight_sum = 0;
    coords_instance_t instance   = pool.instances[self];

    for (uint8_t i = 0; i < COORDS_SIZE; i++)
    {
        sum += instance.coordinates[i];
        weight_sum += coords_weights[i] * instance.coordinates[i];
    }

    if (sum != 0)
    {
        *value = weight_sum / sum;
    }
}