#ifndef _SPI_H
#define _SPI_H

#include <stdint.h>

#define SPI_MAX_BUFFER 15

void
spi_init_master(void);

void
spi_transmittion_start(uint8_t const request[], uint8_t size);

__attribute__((weak)) void
spi_on_response_received_isr(uint8_t response[]);

#endif