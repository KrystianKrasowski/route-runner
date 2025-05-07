#ifndef _DEVICES_OPENCM3_STM32F3_TIMEOUT_GUARD_H
#define _DEVICES_OPENCM3_STM32F3_TIMEOUT_GUARD_H

#include <devices/timeout_guard.h>
#include <stdint.h>

typedef struct
{
    uint32_t       timer;
    notification_t timeout_notification;
} timeout_guard_conf_t;

void
timeout_guard_init(void);

int
timeout_guard_create(device_timeout_guard_t const h_self,
                     timeout_guard_conf_t const  *p_conf);

#endif
