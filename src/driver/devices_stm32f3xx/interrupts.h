#ifndef _DEVICES_STM32F303XX_INTERRUPTS_H
#define _DEVICES_STM32F303XX_INTERRUPTS_H

#include <stdint.h>

void
tim2_on_update_isr(void);

void
spi1_on_response_isr(uint8_t const response[]);

#endif