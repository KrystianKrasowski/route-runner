#include <assert.h>
#include <devices/blink_mock.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    uint8_t last_toggles_num;
} blink_mock_t;

POOL_DECLARE(blink_mock, blink_mock_t, DEVICE_BLINK_INSTANCES_NUM)

static blink_mock_pool_t pool;

int
device_blink_set_toggles(device_blink_t const h_self, uint8_t num)
{
    blink_mock_t *p_self = blink_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    p_self->last_toggles_num = num;

    return RESULT_OK;
}

void
device_blink_mock_init(void)
{
    blink_mock_pool_init(&pool);

    for (int i = 0; i < DEVICE_BLINK_INSTANCES_NUM; i++)
    {
        blink_mock_pool_alloc_at(&pool, i);
    }
}

void
device_blink_mock_deinit(void)
{
    for (int i = 0; i < DEVICE_BLINK_INSTANCES_NUM; i++)
    {
        blink_mock_pool_free(&pool, i);
    }
}

uint8_t
device_blink_mock_verify_toggles_num(device_blink_t const h_self)
{
    blink_mock_t *p_self = blink_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    return p_self->last_toggles_num;
}
