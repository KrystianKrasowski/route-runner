#ifndef _SPI_H
#define _SPI_H

#include <stdint.h>

#define SPI_MAX_BUFFER 15

typedef struct
{
    uint8_t payload[SPI_MAX_BUFFER];
    uint8_t size;
} spi_request_t;

void
spi_init_master(void);

void
spi_transmittion_start(spi_request_t const *request);

__attribute__((weak)) void
spi_on_response_received_isr(uint8_t response[]);

#endif