#ifndef _SPI_TRANSFER_H
#define _SPI_TRANSFER_H

#include "spi.h"
#include <stdint.h>

typedef enum
{
    SPI_TRANSFER_IDLE,
    SPI_TRANSFER_PENDING,
} spi_transfer_status_t;

typedef struct spi_transfer
{
    spi_transfer_status_t status;
    uint8_t               size;
    uint8_t               tx_buffer[SPI_MAX_BUFFER];
    uint8_t               rx_buffer[SPI_MAX_BUFFER];
    uint8_t               tx_index;
    uint8_t               rx_index;
} spi_transfer_t;

typedef enum
{
    SPI_RESULT_SUCCESS,
    SPI_RESULT_ERROR,
    SPI_RESULT_ALREADY_PENDING,
    SPI_RESULT_END_OF_TRANSMISSION,
    SPI_RESULT_END_OF_RECEPTION,
} spi_transfer_result_t;

void
spi_transfer_init(spi_transfer_t volatile *self);

spi_transfer_result_t
spi_transfer_start(spi_transfer_t volatile *self,
                   uint8_t const            request[],
                   uint8_t                  size);

spi_transfer_result_t
spi_transfer_next_tx(spi_transfer_t volatile *self, uint8_t *byte);

spi_transfer_result_t
spi_transfer_put_rx(spi_transfer_t volatile *self, uint8_t byte);

uint8_t
spi_transfer_get_size(spi_transfer_t volatile *self);

void
spi_transfer_get_response(spi_transfer_t volatile *self, uint8_t response[]);

#endif