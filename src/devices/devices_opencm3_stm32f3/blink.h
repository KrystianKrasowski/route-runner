#ifndef _DEVICES_OPENCM3_STM32F3_BLINK_H
#define _DEVICES_OPENCM3_STM32F3_BLINK_H

#include <devices/blink.h>
#include <stdint.h>

typedef struct
{
    uint32_t timer;
    uint8_t  toggles_num;
} blink_conf_t;

void
blink_init(void);

int
blink_create(device_blink_t const h_self, blink_conf_t const *p_conf);

int
blink_update(device_blink_t const h_self);

#endif
