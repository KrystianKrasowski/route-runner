#include <assert.h>
#include <devices/qtrhd06a.h>
#include <devices/qtrhd06a_mock.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    uint8_t values[DEVICE_QTRHD06A_VALUES_LENGTH];
    bool    b_ready;
} qtrhd06a_mock_t;

POOL_DECLARE(qtrhd06a_mock, qtrhd06a_mock_t, DEVICE_QTRHD06A_INSTANCES_NUM)

static qtrhd06a_mock_pool_t pool;

int
device_qtrhd06a_read(device_qtrhd06a_t const h_self, uint8_t values[])
{
    qtrhd06a_mock_t *p_self = qtrhd06a_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    if (p_self->b_ready)
    {
        memcpy(values, p_self->values, sizeof(p_self->values));

        return RESULT_OK;
    }
    else
    {
        return RESULT_NOT_READY;
    }
}

void
device_qtrhd06a_mock_init(void)
{
    qtrhd06a_mock_pool_init(&pool);

    for (int i = 0; i < DEVICE_QTRHD06A_INSTANCES_NUM; i++)
    {
        assert(qtrhd06a_mock_pool_alloc_at(&pool, i));
    }
}

void
device_qtrhd06a_mock_deinit(void)
{
    for (int i = 0; i < DEVICE_QTRHD06A_INSTANCES_NUM; i++)
    {
        qtrhd06a_mock_pool_free(&pool, i);
    }
}

void
device_qtrhd06a_mock_set_values(device_qtrhd06a_t const h_self,
                                uint8_t const           values[])
{
    qtrhd06a_mock_t *p_self = qtrhd06a_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    memcpy(p_self->values, values, sizeof(p_self->values));
}

void
device_qtrhd06a_mock_set_ready(device_qtrhd06a_t const h_self,
                               bool const              b_ready)
{
    qtrhd06a_mock_t *p_self = qtrhd06a_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    p_self->b_ready = b_ready;
}
