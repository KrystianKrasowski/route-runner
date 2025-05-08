#ifndef _DEVICES_OPENCM3_STM32F3_QTRHD06A_H
#define _DEVICES_OPENCM3_STM32F3_QTRHD06A_H

#include "notification.h"
#include <devices/qtrhd06a.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    volatile uint16_t * const p_raw_values;
    uint8_t const             raw_values_length;
    notification_t            notification_id;
} qtrhd06a_conf_t;

void
qtrhd06a_init(void);

int
qtrhd06a_create(device_qtrhd06a_t const h_self, qtrhd06a_conf_t const *p_conf);

#endif
