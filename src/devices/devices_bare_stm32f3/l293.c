#include "devices/l293.h"
#include "l293.h"
#include "sysclock.h"
#include <errno.h>
#include <stm32f3xx.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

// cppcheck-suppress unusedFunction
POOL_DECLARE(l293, l293_instance_t, DEVICE_L293_INSTANCES_NUM)

static l293_pool_t pool;

static inline int
l293_set_left(l293_instance_t const *p_self);

static inline int
l293_set_right(l293_instance_t const *p_self);

static inline int
l293_set_stop(l293_instance_t const *p_self);

void
l293_init(void)
{
    l293_pool_init(&pool);
}

void
l293_create(device_l293_t handle, l293_instance_t *p_instance)
{
    l293_pool_alloc_at(&pool, handle);

    l293_instance_t *p_self = l293_pool_get(&pool, handle);

    memcpy(p_self, p_instance, sizeof(*p_self));
}

int
device_l293_rotate(device_l293_t h_self, device_l293_rotation_t rotation)
{
    l293_instance_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    switch (rotation)
    {
        case DEVICE_L293_ROTATION_LEFT:
            return l293_set_left(p_self);

        case DEVICE_L293_ROTATION_RIGHT:
            return l293_set_right(p_self);

        case DEVICE_L293_ROTATION_STOP:
        default:
            return l293_set_stop(p_self);
    }
}

int
device_l293_enable(device_l293_t h_self, uint8_t duty_cycle)
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
device_l293_disable(device_l293_t h_self)
{
    l293_instance_t const *p_self = l293_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    tim_oc_stop(p_self->pwm_timer, p_self->pwm_channel);

    return RESULT_OK;
}

int
l293_set_left(l293_instance_t const *p_self)
{
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
l293_set_right(l293_instance_t const *p_self)
{
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
l293_set_stop(l293_instance_t const *p_self)
{
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
