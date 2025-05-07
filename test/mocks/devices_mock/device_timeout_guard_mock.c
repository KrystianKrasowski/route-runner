#include <assert.h>
#include <devices/timeout_guard_mock.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    bool started;
    bool timeout;
} timeout_guard_mock_t;

POOL_DECLARE(timeout_guard_mock,
             timeout_guard_mock_t,
             DEVICE_TIMEOUT_GUARD_INSTANCES_NUM)

static timeout_guard_mock_pool_t pool;

int
device_timeout_guard_start(device_timeout_guard_t const h_self)
{
    timeout_guard_mock_t *p_self = timeout_guard_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    p_self->started = true;

    return RESULT_OK;
}

int
device_timeout_guard_stop(device_timeout_guard_t const h_self)
{
    timeout_guard_mock_t *p_self = timeout_guard_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    p_self->started = false;

    return RESULT_OK;
}

int
device_timeout_guard_read(device_timeout_guard_t const h_self)
{
    timeout_guard_mock_t *p_self = timeout_guard_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    if (p_self->timeout)
    {
        return RESULT_TIMEOUT;
    }

    return RESULT_OK;
}

void
device_timeout_guard_mock_init(void)
{
    timeout_guard_mock_pool_init(&pool);

    for (int i = 0; i < DEVICE_TIMEOUT_GUARD_INSTANCES_NUM; i++)
    {
        timeout_guard_mock_pool_alloc_at(&pool, i);
    }
}

void
device_timeout_guard_mock_deinit(void)
{
    for (int i = 0; i < DEVICE_TIMEOUT_GUARD_INSTANCES_NUM; i++)
    {
        timeout_guard_mock_pool_free(&pool, i);
    }
}

bool
device_timeout_guard_mock_is_started(device_timeout_guard_t const h_self)
{
    timeout_guard_mock_t *p_self = timeout_guard_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    return p_self->started;
}

bool
device_timeout_guard_mock_is_stopped(device_timeout_guard_t const h_self)
{
    timeout_guard_mock_t *p_self = timeout_guard_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    return !p_self->started;
}

void
device_timeout_guard_mock_set_ready(device_timeout_guard_t const h_self,
                                    bool const                   ready)
{
    timeout_guard_mock_t *p_self = timeout_guard_mock_pool_get(&pool, h_self);

    assert(NULL != p_self);

    p_self->timeout = ready;
}
