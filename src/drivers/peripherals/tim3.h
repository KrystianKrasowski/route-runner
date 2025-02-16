#ifndef _TIM3_H
#define _TIM3_H

#include <stdint.h>

typedef enum
{
    TIM3_CHANNEL_3,
    TIM3_CHANNEL_4,
} tim3_channel_t;

void
tim3_init(void);

void
tim3_enable(void);

void
tim3_channel_pwm_init(tim3_channel_t channel);

void
tim3_channel_pwm_run(tim3_channel_t channel);

void
tim3_channel_pwm_stop(tim3_channel_t channel);

#endif