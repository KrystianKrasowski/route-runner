#ifndef _SPI_H
#define _SPI_H

#include "gpio.h"
#include <stdint.h>

#define SPI_MAX_BUFFER 15

typedef struct
{
    uint8_t const payload[SPI_MAX_BUFFER];
    uint8_t const size;
    gpio_t       device_select;
} spi_request_t;

void
spi_init_master(void);

void
spi_transmittion_start(spi_request_t *request);

__attribute__((weak)) void
spi_on_response_received_isr(uint8_t const response[]);

#endif