#ifndef _DEVICES_STM32F303XX_INTERRUPTS_H
#define _DEVICES_STM32F303XX_INTERRUPTS_H

#include <stdint.h>

__attribute__((weak)) void
tim2_on_update_isr(void);

__attribute__((weak)) void
spi1_on_response_isr(uint8_t const response[]);

#endif