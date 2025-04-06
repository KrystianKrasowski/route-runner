#ifndef _TIM1_MOCK_H
#define _TIM1_MOCK_H

#include <tim1.h>

void
tim1_ch1_mock_reset(void);

int
tim1_ch1_mock_verify_init_calls(void);

int
tim1_ch1_mock_verify_set_toggles_calls(void);

uint8_t
tim1_ch1_mock_get_applied_toggles(void);

#endif