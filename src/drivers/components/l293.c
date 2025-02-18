#include "l293.h"
#include <tim3.h>

l293_t
l293_create_channel_left(void)
{
    gpio_t a1 = {GPIO_MOTOR_LEFT_A1, GPIO_MODE_OUTPUT, GPIO_STATE_LOW};
    gpio_t a2 = {GPIO_MOTOR_LEFT_A2, GPIO_MODE_OUTPUT, GPIO_STATE_LOW};

    l293_t l293 = {a1, a2, TIM3_CHANNEL_4};

    return l293;
}

l293_t
l293_create_channel_right(void)
{
    gpio_t a1 = {GPIO_MOTOR_RIGHT_A1, GPIO_MODE_OUTPUT, GPIO_STATE_LOW};
    gpio_t a2 = {GPIO_MOTOR_RIGHT_A2, GPIO_MODE_OUTPUT, GPIO_STATE_LOW};

    l293_t l293 = {a1, a2, TIM3_CHANNEL_3};

    return l293;
}

void
l293_init(l293_t *self)
{
    gpio_init(&self->a1);
    gpio_init(&self->a2);
    tim3_init();
    tim3_channel_pwm_init(self->pwm_channel);
    tim3_enable();
}

void
l293_set_left(l293_t *self)
{
    gpio_set_state(&self->a1, GPIO_STATE_HIGH);
    gpio_set_state(&self->a2, GPIO_STATE_LOW);
}

void
l293_set_right(l293_t *self)
{
    gpio_set_state(&self->a1, GPIO_STATE_LOW);
    gpio_set_state(&self->a2, GPIO_STATE_HIGH);
}

void
l293_set_stop(l293_t *self)
{
    gpio_set_state(&self->a1, GPIO_STATE_LOW);
    gpio_set_state(&self->a2, GPIO_STATE_LOW);
}

void
l293_enable(l293_t *self)
{
    tim3_channel_pwm_run(self->pwm_channel);
}

void
l293_disable(l293_t *self)
{
    tim3_channel_pwm_stop(self->pwm_channel);
}

void
l293_stop_running(l293_t *self)
{
    l293_disable(self);
    l293_set_stop(self);
}

void
l293_stop(l293_t *self)
{
    l293_set_stop(self);
    l293_enable(self);
}