#ifndef _TIM2_H
#define _TIM2_H

void
tim2_ch1_init(void);

void
tim2_ch1_compare_isr(void) __attribute__((weak));

#endif