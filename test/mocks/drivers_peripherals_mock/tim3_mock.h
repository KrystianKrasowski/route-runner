#ifndef _TIM3_MOCK_H
#define _TIM3_MOCK_H

#include <stdbool.h>
#include <tim3.h>

int
tim3_mock_verify_init_calls(void);

bool
tim3_mock_verify_enabled(void);

int
tim3_mock_verify_pwm_init_on_channel4(void);

int
tim3_mock_verify_pwm_init_on_channel3(void);

bool
tim3_mock_verify_channel3_running(void);

bool
tim3_mock_verify_channel4_running(void);

void
tim3_mock_reset(void);

#endif