#ifndef _DEVICES_OPENCM3_STM32F3_DUALSHOCK2_H
#define _DEVICES_OPENCM3_STM32F3_DUALSHOCK2_H

#include <devices/dualshock2.h>
#include <stdint.h>

typedef struct
{
    uint32_t const           device_select_port;
    uint16_t const           device_select_pin;
    uint32_t const           spi_dma_port;
    uint8_t const            spi_dma_tx_channel;
    uint8_t const            spi_dma_rx_channel;
    volatile uint8_t * const p_state;
} dualshock2_conf_t;

void
dualshock2_init(void);

int
dualshock2_create(device_dualshock2_t const handle,
                  dualshock2_conf_t const  *p_conf);

int
dualshock2_poll_start(device_dualshock2_t const h_self);

int
dualshock2_poll_end(device_dualshock2_t const h_self);

#endif
