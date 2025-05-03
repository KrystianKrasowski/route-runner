#include "spi_transmittion.h"
#include <errno.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

typedef struct
{
    uint32_t spi_port;
    uint32_t device_select_port;
    uint16_t device_select_pin;
    uint8_t  request[SPI_TRANSMITTION_MAX_SIZE];
    uint8_t  response[SPI_TRANSMITTION_MAX_SIZE];
    uint8_t  payload_size;
    uint8_t  tx_index;
    uint8_t  rx_index;
    bool     busy;
} spi_tx_instance_t;

POOL_DECLARE(spi_tx, spi_tx_instance_t, 1)

static spi_tx_pool_t pool;

static inline void
spi_transmittion_instantiate(spi_transmittion_t const handle);

void
spi_transmittion_init(void)
{
    spi_tx_pool_init(&pool);
    spi_transmittion_instantiate(SPI_TRANSMITTION_SPI1);
}

int
spi_transmittion_start(spi_transmittion_t const       h_self,
                       spi_transmittion_conf_t const *p_conf,
                       uint8_t const                  request[],
                       uint8_t const                  request_size)
{
    spi_tx_instance_t *p_self = spi_tx_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (p_self->busy)
    {
        return RESULT_NOT_READY;
    }

    memset(p_self->response, 0, sizeof(p_self->response));
    memcpy(p_self->request, request, request_size);

    p_self->spi_port           = p_conf->spi_port;
    p_self->device_select_port = p_conf->device_select_port;
    p_self->device_select_pin  = p_conf->device_select_pin;
    p_self->payload_size       = request_size;
    p_self->tx_index           = 0;
    p_self->rx_index           = 0;
    p_self->busy               = true;

    gpio_clear(p_conf->device_select_port, p_conf->device_select_pin);
    spi_enable_tx_buffer_empty_interrupt(p_conf->spi_port);

    return RESULT_OK;
}

int
spi_transmittion_next_tx_byte(spi_transmittion_t const h_self, uint8_t *p_byte)
{
    spi_tx_instance_t *p_self = spi_tx_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (p_self->tx_index < p_self->payload_size)
    {
        *p_byte = p_self->request[p_self->tx_index++];

        return RESULT_OK;
    }

    return RESULT_END_OF_BUFFER;
}

int
spi_transmittion_next_rx_byte(spi_transmittion_t const h_self, uint8_t byte)
{
    spi_tx_instance_t *p_self = spi_tx_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (p_self->rx_index < p_self->payload_size)
    {
        p_self->response[p_self->rx_index++] = byte;
    }

    return (p_self->rx_index < p_self->payload_size) ? RESULT_OK
                                                     : RESULT_END_OF_BUFFER;
}

int
spi_transmittion_end(spi_transmittion_t const h_self, uint8_t response[])
{
    spi_tx_instance_t *p_self = spi_tx_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    gpio_set(p_self->device_select_port, p_self->device_select_pin);
    memcpy(response, p_self->response, p_self->payload_size);

    p_self->busy = false;

    return RESULT_OK;
}

static inline void
spi_transmittion_instantiate(spi_transmittion_t const handle)
{
    if (!spi_tx_pool_alloc_at(&pool, handle))
    {
        return;
    }

    spi_tx_instance_t *p_self = spi_tx_pool_get(&pool, handle);

    memset(p_self, 0, sizeof(*p_self));
}
