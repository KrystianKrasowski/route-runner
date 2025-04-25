#ifndef _DEVICES_STM32F3XX_DUALSHOCK2_H
#define _DEVICES_STM32F3XX_DUALSHOCK2_H

#include "gpio.h"
#include "spi.h"
#include <devices/dualshock2.h>

typedef struct
{
    gpio_t const device_select;
    spi_t const  spi_bus;
} dualshock2_conf_t;

void
dualshock2_init(void);

void
dualshock2_create(dualshock2_t handle, dualshock2_conf_t *p_conf);

#endif
