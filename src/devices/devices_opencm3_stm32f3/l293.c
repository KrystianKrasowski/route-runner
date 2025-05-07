#include "l293.h"
#include <errno.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <utils/pool.h>
#include <utils/result.h>

// cppcheck-suppress unusedFunction
POOL_DECLARE(l293, l293_conf_t, 2)

static l293_pool_t pool;

static inline void
l293_set_left(l293_conf_t const *p_self);

static inline void
l293_set_right(l293_conf_t const *p_self);

static inline void
l293_set_stop(l293_conf_t const *p_self);

void
l293_init(void)
{
    l293_pool_init(&pool);
}

int
l293_create(device_l293_t const h_self, l293_conf_t const *p_conf)
{
    if (!l293_pool_alloc_at(&pool, h_self))
    {
        return -ENOMEM;
    }

    l293_conf_t *p_self = l293_pool_get(&pool, h_self);

    memcpy(p_self, p_conf, sizeof(*p_self));

    return RESULT_OK;
}

int
device_l293_rotate(device_l293_t h_self, device_l293_rotation_t rotation)
{
    l293_conf_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    switch (rotation)
    {
        case DEVICE_L293_ROTATION_LEFT:
            l293_set_left(p_self);
            break;

        case DEVICE_L293_ROTATION_RIGHT:
            l293_set_right(p_self);
            break;

        case DEVICE_L293_ROTATION_STOP:
        default:
            l293_set_stop(p_self);
    }

    return RESULT_OK;
}

int
device_l293_enable(device_l293_t h_self, uint8_t duty_cycle)
{
    l293_conf_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (duty_cycle > 100)
    {
        duty_cycle = 100;
    }

    timer_set_oc_value(p_self->pwm_timer, p_self->pwm_channel, duty_cycle);
    timer_enable_oc_output(p_self->pwm_timer, p_self->pwm_channel);

    return RESULT_OK;
}

int
device_l293_disable(device_l293_t h_self)
{
    l293_conf_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    timer_disable_oc_output(p_self->pwm_timer, p_self->pwm_channel);

    return RESULT_OK;
}

static inline void
l293_set_left(l293_conf_t const *p_self)
{
    gpio_set(p_self->gpio_port_1, p_self->gpio_pin_1);
    gpio_clear(p_self->gpio_port_2, p_self->gpio_pin_2);
}

static inline void
l293_set_right(l293_conf_t const *p_self)
{
    gpio_clear(p_self->gpio_port_1, p_self->gpio_pin_1);
    gpio_set(p_self->gpio_port_2, p_self->gpio_pin_2);
}

static inline void
l293_set_stop(l293_conf_t const *p_self)
{
    gpio_clear(p_self->gpio_port_1, p_self->gpio_pin_1);
    gpio_clear(p_self->gpio_port_2, p_self->gpio_pin_2);
}
