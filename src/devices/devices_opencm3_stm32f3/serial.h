#ifndef _DEVICES_OPENCM3_STM32F3_SERIAL_H
#define _DEVICES_OPENCM3_STM32F3_SERIAL_H

#include "notification.h"
#include <devices/serial.h>
#include <stdint.h>

typedef struct
{
    notification_t notification_rx;
    notification_t notification_tx;
    uint32_t       dma_port;
    uint8_t        dma_channel;
} serial_conf_t;

void
serial_init(void);

int
serial_create(device_serial_t const h_self, serial_conf_t const *p_conf);

int
serial_transmit(device_serial_t const h_self);

#endif
