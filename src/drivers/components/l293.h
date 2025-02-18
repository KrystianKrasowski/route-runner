#ifndef _L293_H
#define _L293_H

#include <gpio.h>
#include <tim3.h>

typedef enum
{
    L293_PWM_CHANNEL_3,
    L293_PWM_CHANNEL_4,
} l293_pwm_channel_t;

typedef struct l293
{
    gpio_t         a1;
    gpio_t         a2;
    tim3_channel_t pwm_channel;
} l293_t;

l293_t
l293_create_channel_left(void);

l293_t
l293_create_channel_right(void);

void
l293_init(l293_t *self);

void
l293_set_left(l293_t *self);

void
l293_set_right(l293_t *self);

void
l293_set_stop(l293_t *self);

void
l293_enable(l293_t *self);

void
l293_disable(l293_t *self);

void
l293_stop_running(l293_t *self);

void
l293_stop(l293_t *self);

#endif