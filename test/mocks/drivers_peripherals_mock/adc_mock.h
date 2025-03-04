#ifndef _ADC_MOCK_H
#define _ADC_MOCK_H

#include <adc.h>

int
adc_mock_verify_init_calls(void);

int
adc_mock_verify_on_calls(void);

int
adc_mock_verity_start_calls(void);

void
adc_mock_reset(void);

#endif