#include "spi.h"
#include "interrupts.h"
#include "stm32f303x8.h"
#include <errno.h>
#include <stm32f3xx.h>
#include <string.h>
#include <utils/pool.h>
#include <utils/result.h>

#define SPI_INSTANCES_NUM    1
#define SPI_MAX_PAYLOAD_SIZE 9

typedef struct
{
    uint8_t request[SPI_MAX_PAYLOAD_SIZE];
    uint8_t response[SPI_MAX_PAYLOAD_SIZE];
    uint8_t size;
    uint8_t tx_index;
    uint8_t rx_index;
    bool    busy;
    gpio_t  device_select;
} spi_transfer_t;

typedef struct
{
    SPI_TypeDef   *SPIx;
    IRQn_Type      IRQn;
    spi_transfer_t transfer;
} spi_instance_t;

POOL_DECLARE(spi, spi_instance_t, SPI_INSTANCES_NUM)

static spi_pool_t pool;

static inline void
rcc_init(void);

static inline int
create_spi_instance(SPI_TypeDef *SPIx, IRQn_Type IRQn, spi_t handle);

static inline int
transfer_prepare(spi_transfer_t *p_self,
                 uint8_t         payload[],
                 uint8_t         size,
                 gpio_t          device);

static inline int
transfer_get_next_tx_byte(spi_transfer_t *p_self, uint8_t *p_next_byte);

static inline int
transfer_put_next_rx_byte(spi_transfer_t *p_self, uint8_t byte);

static void
transfer_complete(spi_transfer_t *p_self, uint8_t response[]);

void
spi_init(void)
{
    rcc_init();
    spi_pool_init(&pool);
    create_spi_instance(SPI1, SPI1_IRQn, PERIPH_SPI1);
}

int
spi_set_baud_rate(spi_t h_self, spi_baud_rate_t baud_rate)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->SPIx->CR1 |= (baud_rate << SPI_CR1_BR_Pos);

    return RESULT_OK;
}

int
spi_set_clock_phase(spi_t h_self, spi_cpha_t clock_phase)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (PERIPH_SPI_CPHA_DATA_ON_1ST_TRANS == clock_phase)
    {
        p_self->SPIx->CR1 &= ~SPI_CR1_CPHA;
    }
    else
    {
        p_self->SPIx->CR1 |= SPI_CR1_CPHA;
    }

    return RESULT_OK;
}

int
spi_set_clock_polarity(spi_t h_self, spi_cpol_t clock_polarity)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (PERIPH_SPI_CPOL_IDLE_LOW == clock_polarity)
    {
        p_self->SPIx->CR1 &= ~SPI_CR1_CPOL;
    }
    else
    {
        p_self->SPIx->CR1 |= SPI_CR1_CPOL;
    }

    return RESULT_OK;
}

int
spi_set_full_duplex(spi_t h_self)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->SPIx->CR1 &= ~SPI_CR1_RXONLY;

    return RESULT_OK;
}

int
spi_set_frame_format(spi_t h_self, spi_frame_format_t format)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (PERIPH_SPI_FRAME_MSBFIRST == format)
    {
        p_self->SPIx->CR1 &= ~SPI_CR1_LSBFIRST;
    }
    else
    {
        p_self->SPIx->CR1 |= SPI_CR1_LSBFIRST;
    }

    return RESULT_OK;
}

int
spi_set_software_slave_management(spi_t h_self)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->SPIx->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;

    return RESULT_OK;
}

int
spi_set_master_mode(spi_t h_self)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->SPIx->CR1 |= SPI_CR1_MSTR;

    return RESULT_OK;
}

int
spi_set_data_size(spi_t h_self, spi_data_size_t size)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->SPIx->CR2 &= ~SPI_CR2_DS;
    p_self->SPIx->CR2 |= (size << SPI_CR2_DS_Pos);

    return RESULT_OK;
}

int
spi_set_rx_interrupts(spi_t h_self, spi_rx_interrupt_treshold_t treshold)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->SPIx->CR2 |= SPI_CR2_RXNEIE;

    if (PERIPH_SPI_RX_INTERRUPT_8BIT == treshold)
    {
        p_self->SPIx->CR2 |= SPI_CR2_FRXTH;
    }
    else
    {
        p_self->SPIx->CR2 &= ~SPI_CR2_FRXTH;
    }

    NVIC_EnableIRQ(p_self->IRQn);

    return RESULT_OK;
}

int
spi_enable(spi_t h_self)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    p_self->SPIx->CR1 |= SPI_CR1_SPE;

    return RESULT_OK;
}

int
spi_transmit(spi_t h_self, uint8_t payload[], uint8_t size, gpio_t device)
{
    spi_instance_t *p_self = spi_pool_get(&pool, h_self);

    if (NULL == p_self)
    {
        return -ENODEV;
    }

    if (transfer_prepare(&p_self->transfer, payload, size, device) != RESULT_OK)
    {
        return RESULT_NOT_READY;
    }

    p_self->SPIx->CR2 |= SPI_CR2_TXEIE;

    return RESULT_OK;
}

void
// cppcheck-suppress unusedFunction
SPI1_IRQHandler(void)
{
    spi_instance_t *p_spi = spi_pool_get(&pool, PERIPH_SPI1);

    if (NULL == p_spi)
    {
        return;
    }

    // tx register empty - ready to put new byte
    if (SPI1->SR & SPI_SR_TXE)
    {
        uint8_t byte;

        if (transfer_get_next_tx_byte(&p_spi->transfer, &byte) == RESULT_OK)
        {
            *(__IO uint8_t *)(&SPI1->DR) = byte;
        }
        else
        {
            SPI1->CR2 &= ~SPI_CR2_TXEIE;
        }
    }

    // rx register full - ready to receive new byte
    if (SPI1->SR & SPI_SR_RXNE)
    {
        uint8_t byte   = (uint8_t)SPI1->DR;
        int     result = transfer_put_next_rx_byte(&p_spi->transfer, byte);

        if (RESULT_BUFFER_FULL == result)
        {
            uint8_t response[SPI_MAX_PAYLOAD_SIZE];
            transfer_complete(&p_spi->transfer, response);
            spi1_on_response_isr(response);
        }
    }
}

static inline void
rcc_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
}

static inline int
create_spi_instance(SPI_TypeDef *SPIx, IRQn_Type IRQn, spi_t handle)
{
    if (!spi_pool_alloc_at(&pool, handle))
    {
        return -ENOMEM;
    }

    spi_instance_t *instance = spi_pool_get(&pool, handle);

    instance->SPIx = SPIx;
    instance->IRQn = IRQn;

    memset(&instance->transfer, 0, sizeof(instance->transfer));

    return RESULT_OK;
}

static inline int
transfer_prepare(spi_transfer_t *p_self,
                 uint8_t         payload[],
                 uint8_t         size,
                 gpio_t          device)
{
    if (p_self->busy)
    {
        return RESULT_NOT_READY;
    }

    p_self->busy          = true;
    p_self->size          = size;
    p_self->device_select = device;

    memcpy(p_self->request, payload, size);
    gpio_set_state(p_self->device_select, PERIPH_GPIO_STATE_LOW);

    return RESULT_OK;
}

static inline int
transfer_get_next_tx_byte(spi_transfer_t *p_self, uint8_t *p_next_byte)
{
    if (p_self->tx_index < p_self->size)
    {
        *p_next_byte = p_self->request[p_self->tx_index++];

        return RESULT_OK;
    }

    return RESULT_BUFFER_FULL;
}

static inline int
transfer_put_next_rx_byte(spi_transfer_t *p_self, uint8_t byte)
{
    if (p_self->rx_index < p_self->size)
    {
        p_self->response[p_self->rx_index++] = byte;
    }

    return (p_self->rx_index < p_self->size) ? RESULT_OK : RESULT_BUFFER_FULL;
}

static void
transfer_complete(spi_transfer_t *p_self, uint8_t response[])
{
    gpio_set_state(p_self->device_select, PERIPH_GPIO_STATE_HIGH);
    memcpy(response, p_self->response, p_self->size);
    memset(p_self, 0, sizeof(*p_self));
}
