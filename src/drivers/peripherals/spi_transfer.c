#include "spi_transfer.h"
#include <string.h>

void
spi_transfer_init(spi_transfer_t volatile *self)
{
    self->status        = SPI_TRANSFER_IDLE;
    self->size          = 0;
    self->tx_index      = 0;
    self->rx_index      = 0;
    self->device_select = NULL;

    for (uint8_t i = 0; i < SPI_MAX_BUFFER; i++)
    {
        self->tx_buffer[i] = 0;
        self->rx_buffer[i] = 0;
    }
}

spi_transfer_result_t
spi_transfer_start(spi_transfer_t volatile *self, spi_request_t *request)
{
    if (self->status == SPI_TRANSFER_IDLE)
    {
        self->status        = SPI_TRANSFER_PENDING;
        self->size          = request->size;
        self->device_select = &request->device_select;

        for (uint8_t i = 0; i < self->size; i++)
        {
            self->tx_buffer[i] = request->payload[i];
        }

        gpio_set_state(self->device_select, GPIO_STATE_LOW);

        return SPI_RESULT_SUCCESS;
    }

    return SPI_RESULT_ALREADY_PENDING;
}

spi_transfer_result_t
spi_transfer_next_tx(spi_transfer_t volatile *self, uint8_t *byte)
{
    if (self->tx_index < self->size)
    {
        *byte = self->tx_buffer[self->tx_index++];

        return SPI_RESULT_SUCCESS;
    }

    return SPI_RESULT_END_OF_TRANSMISSION;
}

spi_transfer_result_t
spi_transfer_put_rx(spi_transfer_t volatile *self, uint8_t byte)
{
    if (self->rx_index < self->size)
    {
        self->rx_buffer[self->rx_index++] = byte;
    }

    if (self->rx_index >= self->size)
    {
        gpio_set_state(self->device_select, GPIO_STATE_HIGH);
        return SPI_RESULT_END_OF_RECEPTION;
    }

    return SPI_RESULT_SUCCESS;
}

uint8_t
spi_transfer_get_size(spi_transfer_t volatile const *self)
{
    return self->size;
}

void
spi_transfer_get_response(spi_transfer_t volatile *self, uint8_t response[])
{
    for (uint8_t i = 0; i < self->size; i++)
    {
        response[i] = self->rx_buffer[i];
    }
}