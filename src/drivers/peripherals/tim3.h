#ifndef _TIM3_H
#define _TIM3_H

#include <stdint.h>

void
tim3_init(void);

void
tim3_enable(void);

void
tim3_ch3_pwm_init(void);

void
tim3_ch3_pwm_set_duty_cycle(uint8_t percentage);

void
tim3_ch3_pwm_run(void);

void
tim3_ch3_pwm_stop(void);

void
tim3_ch4_pwm_init(void);

void
tim3_ch4_pwm_set_duty_cycle(uint8_t percentage);

void
tim3_ch4_pwm_run(void);

void
tim3_ch4_pwm_stop(void);

#endif