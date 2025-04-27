#ifndef _DEVICES_STM32F303XX_SPI_H
#define _DEVICES_STM32F303XX_SPI_H

#include "gpio.h"
#include <stdint.h>

typedef enum
{
    PERIPH_SPI1,
} spi_t;

typedef enum
{
    PERIPH_SPI_BR_PRESC_2   = 0,
    PERIPH_SPI_BR_PRESC_4   = 1,
    PERIPH_SPI_BR_PRESC_8   = 2,
    PERIPH_SPI_BR_PRESC_16  = 3,
    PERIPH_SPI_BR_PRESC_32  = 4,
    PERIPH_SPI_BR_PRESC_64  = 5,
    PERIPH_SPI_BR_PRESC_128 = 6,
    PERIPH_SPI_BR_PRESC_256 = 7,
} spi_baud_rate_t;

typedef enum
{
    PERIPH_SPI_CPHA_DATA_ON_1ST_TRANS,
    PERIPH_SPI_CPHA_DATA_ON_2ND_TRANS,
} spi_cpha_t;

typedef enum
{
    PERIPH_SPI_CPOL_IDLE_LOW,
    PERIPH_SPI_CPOL_IDLE_HIGH,
} spi_cpol_t;

typedef enum
{
    PERIPH_SPI_FRAME_LSBFIRST,
    PERIPH_SPI_FRAME_MSBFIRST,
} spi_frame_format_t;

typedef enum
{
    PERIPH_SPI_DS_4BIT = 3,
    PERIPH_SPI_DS_5BIT = 4,
    PERIPH_SPI_DS_6BIT = 5,
    PERIPH_SPI_DS_7BIT = 6,
    PERIPH_SPI_DS_8BIT = 7,
    // Other data sizes are unsupported at this moment due to unnecessary memory
    // consumption
} spi_data_size_t;

typedef enum
{
    PERIPH_SPI_RX_INTERRUPT_16BIT,
    PERIPH_SPI_RX_INTERRUPT_8BIT,
} spi_rx_interrupt_treshold_t;

void
spi_init(void);

int
spi_set_baud_rate(spi_t h_self, spi_baud_rate_t baud_rate);

int
spi_set_clock_phase(spi_t h_self, spi_cpha_t clock_phase);

int
spi_set_clock_polarity(spi_t h_self, spi_cpol_t clock_polarity);

int
spi_set_full_duplex(spi_t h_self);

int
spi_set_frame_format(spi_t h_self, spi_frame_format_t format);

int
spi_set_software_slave_management(spi_t h_self);

int
spi_set_master_mode(spi_t h_self);

int
spi_set_data_size(spi_t h_self, spi_data_size_t size);

int
spi_set_rx_interrupts(spi_t h_self, spi_rx_interrupt_treshold_t treshold);

int
spi_enable(spi_t h_self);

int
spi_transmit(spi_t h_self, uint8_t payload[], uint8_t size, gpio_t device);

#endif
