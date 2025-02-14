#ifndef _TIM3_H
#define _TIM3_H

void
tim3_ch1_init(void);

void
tim3_ch1_compare_isr(void) __attribute__((weak));

#endif