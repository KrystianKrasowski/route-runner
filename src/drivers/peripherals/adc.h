#ifndef _ADC_H
#define _ADC_H

#include <stdint.h>

#define ADC_BUFFER_SIZE 40

void
adc_init();

void
adc_on(void);

void
adc_off(void);

void
adc_start(void);

void
adc_stop(void);

__attribute__((weak)) void
adc_sequence_complete_isr(uint32_t value[]);

#endif