#ifndef _DEVICES_OPENCM3_STM32F3_SPI_TRANSMISSION_H_H
#define _DEVICES_OPENCM3_STM32F3_SPI_TRANSMISSION_H_H

#include <stdint.h>

#define SPI_TRANSMITTION_MAX_SIZE 9

typedef struct
{
    uint32_t const spi_port;
    uint32_t const device_select_port;
    uint16_t const device_select_pin;
} spi_transmittion_conf_t;

typedef enum
{
    SPI_TRANSMITTION_SPI1 = 0,
} spi_transmittion_t;

void
spi_transmittion_init(void);

int
spi_transmittion_start(spi_transmittion_t const       h_self,
                       spi_transmittion_conf_t const *p_conf,
                       uint8_t const                  request[],
                       uint8_t const                  request_size);

int
spi_transmittion_next_tx_byte(spi_transmittion_t const h_self, uint8_t *p_byte);

int
spi_transmittion_next_rx_byte(spi_transmittion_t const h_self,
                              uint8_t const            byte);

int
spi_transmittion_end(spi_transmittion_t const h_self, uint8_t response[]);

#endif
