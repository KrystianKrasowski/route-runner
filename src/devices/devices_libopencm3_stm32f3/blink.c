#include "blink.h"
#include <errno.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    uint32_t         timer;
    uint32_t         gpio_port;
    uint16_t         gpio_pin;
    uint8_t          sequence;
    volatile uint8_t toggles_cnt;
} blink_instance_t;

// cppcheck-suppress unusedFunction
POOL_DECLARE(blink, blink_instance_t, DEVICE_BLINK_INSTANCES_NUM)

static blink_pool_t pool;

int
device_blink_set_sequence(device_blink_t const h_self, uint8_t seq)
{
    blink_instance_t *p_self = blink_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    gpio_clear(p_self->gpio_port, p_self->gpio_pin);
    timer_disable_counter(p_self->timer);

    p_self->toggles_cnt = 0;
    p_self->sequence    = seq;

    timer_enable_counter(p_self->timer);

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
    p_self->gpio_port   = p_conf->gpio_port;
    p_self->gpio_pin    = p_conf->gpio_pin;
    p_self->sequence    = p_conf->sequence;
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

    if (p_self->sequence & (1 << p_self->toggles_cnt))
    {
        gpio_set(p_self->gpio_port, p_self->gpio_pin);
    }
    else
    {
        gpio_clear(p_self->gpio_port, p_self->gpio_pin);
    }

    ++p_self->toggles_cnt;

    if (p_self->toggles_cnt > 7)
    {
        p_self->toggles_cnt = 0;
    }

    return RESULT_OK;
}
