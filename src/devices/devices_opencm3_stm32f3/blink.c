#include "blink.h"
#include <errno.h>
#include <libopencm3/stm32/timer.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    uint32_t         timer;
    volatile uint8_t toggles_cnt;
    uint8_t          toggles_num;
} blink_instance_t;

POOL_DECLARE(blink, blink_instance_t, 1)

#define HALF_INTERVAL 125

static blink_pool_t pool;

static inline uint32_t
count_period(blink_instance_t *p_self);

int
device_blink_set_toggles(device_blink_t const h_self, uint8_t num)
{
    blink_instance_t *p_self = blink_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    num = num % 8;

    if (0 == num)
    {
        num = 8;
    }

    p_self->toggles_num = num;

    return RESULT_OK;
}

void
blink_init(void)
{
    blink_pool_init(&pool);
}

int
blink_create(device_blink_t const h_self, blink_conf_t const *p_conf)
{
    if (!blink_pool_alloc_at(&pool, h_self))
    {
        return -ENOMEM;
    }

    blink_instance_t *p_self = blink_pool_get(&pool, h_self);

    p_self->timer       = p_conf->timer;
    p_self->toggles_num = p_conf->toggles_num;
    p_self->toggles_cnt = 0;

    timer_enable_counter(p_self->timer);

    return RESULT_OK;
}

int
blink_update(device_blink_t const h_self)
{
    blink_instance_t *p_self = blink_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (0 == p_self->toggles_cnt)
    {
        timer_set_period(p_self->timer, 125 - 1);
    }

    p_self->toggles_cnt++;

    if (p_self->toggles_cnt >= p_self->toggles_num)
    {
        p_self->toggles_cnt = 0;
        timer_set_period(p_self->timer, count_period(p_self) - 1);
    }

    return RESULT_OK;
}

static inline uint32_t
count_period(blink_instance_t *p_self)
{
    return 1000 - p_self->toggles_num * HALF_INTERVAL + HALF_INTERVAL;
}
