#include "l293.h"
#include "gpio.h"
#include "sysclock.h"
#include "tim.h"
#include <devices/l293.h>
#include <errno.h>
#include <stm32f3xx.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    gpio_t        driver_channel_1;
    gpio_t        driver_channel_2;
    tim_t         pwm_timer;
    tim_channel_t pwm_channel;
} l293_instance_t;

// cppcheck-suppress unusedFunction
POOL_DECLARE(l293, l293_instance_t, 2)

static l293_pool_t pool;

static inline void
create_instance_12(void);

static inline void
create_instance_34(void);

void
l293_init(void)
{
    l293_pool_init(&pool);
    create_instance_12();
    create_instance_34();
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

    tim_run_out_compare(p_self->pwm_timer, p_self->pwm_channel, duty_cycle);

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

    tim_stop_out_compare(p_self->pwm_timer, p_self->pwm_channel);

    return RESULT_OK;
}

static inline void
create_instance_12(void)
{
    l293_pool_alloc_at(&pool, DEVICES_L293_CHANNEL_12);

    l293_instance_t *p_self = l293_pool_get(&pool, DEVICES_L293_CHANNEL_12);

    p_self->driver_channel_1 = PERIPH_GPIO_PA12;
    p_self->driver_channel_2 = PERIPH_GPIO_PA10;
    p_self->pwm_timer        = PERIPH_TIM3;
    p_self->pwm_channel      = PERIPH_TIM_CHANNEL_3;
}

static inline void
create_instance_34(void)
{
    l293_pool_alloc_at(&pool, DEVICES_L293_CHANNEL_34);

    l293_instance_t *p_self = l293_pool_get(&pool, DEVICES_L293_CHANNEL_34);

    p_self->driver_channel_1 = PERIPH_GPIO_PB6;
    p_self->driver_channel_2 = PERIPH_GPIO_PB7;
    p_self->pwm_timer        = PERIPH_TIM3;
    p_self->pwm_channel      = PERIPH_TIM_CHANNEL_4;
}