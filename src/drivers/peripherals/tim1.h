#ifndef _TIM1_H
#define _TIM1_H

#include <stdint.h>

void
tim1_ch1_init(void);

void
tim1_ch1_set_toggles(uint8_t count);

#endif