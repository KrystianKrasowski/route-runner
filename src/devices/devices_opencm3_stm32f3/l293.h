#ifndef _DEVICES_OPENCM3_STM32F3_L293_H
#define _DEVICES_OPENCM3_STM32F3_L293_H

#include <devices/l293.h>
#include <libopencm3/stm32/timer.h>
#include <stdint.h>

typedef struct
{
    uint32_t       gpio_port_1;
    uint16_t       gpio_pin_1;
    uint32_t       gpio_port_2;
    uint16_t       gpio_pin_2;
    uint32_t       pwm_timer;
    enum tim_oc_id pwm_channel;
} l293_conf_t;

void
l293_init(void);

int
l293_create(device_l293_t h_self, l293_conf_t *p_conf);

#endif
