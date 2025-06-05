#ifndef _DEVICES_OPENCM3_STM32F3_SERIAL_IN_H
#define _DEVICES_OPENCM3_STM32F3_SERIAL_IN_H

#include "notification.h"
#include <devices/serial_in.h>

void
serial_in_init(void);

int
serial_in_create(device_serial_in_t const h_self,
                 notification_t const     notification_id);

#endif
