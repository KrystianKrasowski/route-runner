#ifndef _SPI_H
#define _SPI_H

#include "gpio.h"
#include <stdint.h>

void
spi_init_master(void);

void
spi_transmittion_start(gpio_t *gpio, uint8_t request[], uint8_t size);

__attribute__((weak)) void
spi_on_response_received_isr(uint8_t volatile resposne[], uint8_t size);

#endif