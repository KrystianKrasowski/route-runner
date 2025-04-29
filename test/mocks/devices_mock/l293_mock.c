#include "devices/l293.h"
#include <assert.h>
#include <devices/l293_mock.h>
#include <stdint.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    device_l293_mock_rotation_t rotation;
    bool                        enabled;
    uint8_t                     duty_cycle;
} l293_mock_instance_t;

POOL_DECLARE(l293_mock, l293_mock_instance_t, DEVICES_L293_INSTANCES_NUM)

static l293_mock_pool_t pool;

void
devices_l293_mock_init(void)
{
    l293_mock_pool_init(&pool);

    for (int i = 0; i < DEVICES_L293_INSTANCES_NUM; i++)
    {
        assert(l293_mock_pool_alloc_at(&pool, i));

        l293_mock_instance_t *p_mock = l293_mock_pool_get(&pool, i);

        p_mock->rotation   = L293_MOCK_ROTATION_STOP;
        p_mock->enabled    = false;
        p_mock->duty_cycle = 0;
    }
}

void
devices_l293_mock_deinit(void)
{
    for (int i = 0; i < DEVICES_L293_INSTANCES_NUM; i++)
    {
        l293_mock_pool_free(&pool, i);
    }
}

int
devices_l293_set_left(device_l293_t h_self)
{
    l293_mock_instance_t *p_self = l293_mock_pool_get(&pool, h_self);

    assert(p_self != NULL);

    p_self->rotation = L293_MOCK_ROTATION_LEFT;

    return RESULT_OK;
}

int
devices_l293_set_right(device_l293_t h_self)
{
    l293_mock_instance_t *p_self = l293_mock_pool_get(&pool, h_self);

    assert(p_self != NULL);

    p_self->rotation = L293_MOCK_ROTATION_RIGHT;

    return RESULT_OK;
}

int
devices_l293_set_stop(device_l293_t h_self)
{
    l293_mock_instance_t *p_self = l293_mock_pool_get(&pool, h_self);

    assert(p_self != NULL);

    p_self->rotation = L293_MOCK_ROTATION_STOP;

    return RESULT_OK;
}

int
devices_l293_enable(device_l293_t h_self, uint8_t duty_cycle)
{
    l293_mock_instance_t *p_self = l293_mock_pool_get(&pool, h_self);

    assert(p_self != NULL);

    p_self->enabled    = true;
    p_self->duty_cycle = duty_cycle;

    return RESULT_OK;
}

int
devices_l293_disable(device_l293_t h_self)
{
    l293_mock_instance_t *p_self = l293_mock_pool_get(&pool, h_self);

    assert(p_self != NULL);

    p_self->enabled    = false;
    p_self->duty_cycle = 0;

    return RESULT_OK;
}

device_l293_mock_rotation_t
devices_l293_mock_verify_rotation(device_l293_t const h_self)
{
    l293_mock_instance_t *p_self = l293_mock_pool_get(&pool, h_self);

    assert(p_self != NULL);

    return p_self->rotation;
}

bool
devices_l293_mock_is_enabled(device_l293_t const h_self)
{
    l293_mock_instance_t *p_self = l293_mock_pool_get(&pool, h_self);

    assert(p_self != NULL);

    return p_self->enabled;
}

uint8_t
devices_l293_mock_verify_duty_cycle(device_l293_t const h_self)
{
    l293_mock_instance_t *p_self = l293_mock_pool_get(&pool, h_self);

    assert(p_self != NULL);

    return p_self->duty_cycle;
}
