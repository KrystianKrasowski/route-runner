#ifndef _CORE_CM4_STUB_H
#define _CORE_CM4_STUB_H

#define SPI1_IRQn 0
#define TIM3_IRQn 0

void
NVIC_EnableIRQ(int vector);

#endif