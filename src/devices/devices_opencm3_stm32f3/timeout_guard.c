#include "notification.h"
#include "timeout_guard.h"
#include <errno.h>
#include <libopencm3/stm32/timer.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

POOL_DECLARE(timeout_guard,
             timeout_guard_conf_t,
             DEVICE_TIMEOUT_GUARD_INSTANCES_NUM)

static timeout_guard_pool_t pool;

int
device_timeout_guard_start(device_timeout_guard_t const h_self)
{
    timeout_guard_conf_t *p_self = timeout_guard_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    timer_enable_counter(p_self->timer);

    return RESULT_OK;
}

int
device_timeout_guard_stop(device_timeout_guard_t const h_self)
{
    timeout_guard_conf_t *p_self = timeout_guard_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    timer_disable_counter(p_self->timer);
    timer_set_counter(p_self->timer, 0);

    return RESULT_OK;
}

int
device_timeout_guard_read(device_timeout_guard_t const h_self)
{
    timeout_guard_conf_t *p_self = timeout_guard_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (notification_take(p_self->timeout_notification))
    {
        return RESULT_TIMEOUT;
    }

    return RESULT_OK;
}

void
timeout_guard_init(void)
{
    timeout_guard_pool_init(&pool);
}

int
timeout_guard_create(device_timeout_guard_t const h_self,
                     timeout_guard_conf_t const  *p_conf)
{
    if (!timeout_guard_pool_alloc_at(&pool, h_self))
    {
        return -ENOMEM;
    }

    timeout_guard_conf_t *p_self = timeout_guard_pool_get(&pool, h_self);

    memcpy(p_self, p_conf, sizeof(*p_self));

    return RESULT_OK;
}
