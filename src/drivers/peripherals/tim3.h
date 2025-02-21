#ifndef _TIM3_H
#define _TIM3_H

#include <stdint.h>

typedef enum
{
    TIM3_CHANNEL_3,
    TIM3_CHANNEL_4,
} tim3_pwm_channel_t;

typedef struct tim3_pwm
{
    tim3_pwm_channel_t const channel;
    uint8_t                  duty_cycle;
} tim3_pwm_t;

void
tim3_init(void);

void
tim3_enable(void);

void
tim3_pwm_init(tim3_pwm_t *self);

void
tim3_pwm_run(tim3_pwm_t *self);

void
tim3_pwm_stop(tim3_pwm_t *self);

void
tim3_pwm_set_duty_cycle(tim3_pwm_t *self, uint8_t duty_cycle);

#endif