#include "l293.h"
#include "sysclock.h"
#include <errno.h>
#include <stm32f3xx.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

// cppcheck-suppress unusedFunction
POOL_DECLARE(l293, l293_instance_t, 2)

static l293_pool_t pool;

void
l293_init(void)
{
    l293_pool_init(&pool);
}

void
l293_create(l293_t handle, l293_instance_t *p_instance)
{
    l293_pool_alloc_at(&pool, handle);

    l293_instance_t *p_self = l293_pool_get(&pool, handle);

    memcpy(p_self, p_instance, sizeof(*p_self));
}

int
devices_l293_set_left(l293_t h_self)
{
    l293_instance_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (gpio_set_state(p_self->driver_channel_1, PERIPH_GPIO_STATE_HIGH) < 0)
    {
        return -ENODEV;
    }

    if (gpio_set_state(p_self->driver_channel_2, PERIPH_GPIO_STATE_LOW) < 0)
    {
        return -ENODEV;
    }

    return RESULT_OK;
}

int
devices_l293_set_right(l293_t h_self)
{
    l293_instance_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (gpio_set_state(p_self->driver_channel_1, PERIPH_GPIO_STATE_LOW) < 0)
    {
        return -ENODEV;
    }

    if (gpio_set_state(p_self->driver_channel_2, PERIPH_GPIO_STATE_HIGH) < 0)
    {
        return -ENODEV;
    }

    return RESULT_OK;
}

int
devices_l293_set_stop(l293_t h_self)
{
    l293_instance_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (gpio_set_state(p_self->driver_channel_1, PERIPH_GPIO_STATE_LOW) < 0)
    {
        return -ENODEV;
    }

    if (gpio_set_state(p_self->driver_channel_2, PERIPH_GPIO_STATE_LOW) < 0)
    {
        return -ENODEV;
    }

    return RESULT_OK;
}

int
devices_l293_enable(l293_t h_self, uint8_t duty_cycle)
{
    l293_instance_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (duty_cycle > 100)
    {
        duty_cycle = 100;
    }

    tim_oc_run(p_self->pwm_timer, p_self->pwm_channel, duty_cycle);

    return RESULT_OK;
}

int
devices_l293_disable(l293_t h_self)
{
    l293_instance_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    tim_oc_stop(p_self->pwm_timer, p_self->pwm_channel);

    return RESULT_OK;
}