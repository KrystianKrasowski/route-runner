#ifndef _DEVICES_OPENCM3_STM32F3_SERIAL_H
#define _DEVICES_OPENCM3_STM32F3_SERIAL_H

#include "notification.h"
#include <devices/serial.h>

void
serial_init(void);

int
serial_create(device_serial_t const h_self,
              notification_t const  notification_id);

#endif
