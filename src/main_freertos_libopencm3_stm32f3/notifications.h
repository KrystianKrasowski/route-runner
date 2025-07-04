#ifndef _MAIN_FREERTOS_NOTIFICATIONS_PORT_H
#define _MAIN_FREERTOS_NOTIFICATIONS_PORT_H

#include "FreeRTOS.h"
#include "task.h"
#include <devices/port.h>

void
notifications_init(void);

// MUST NOT be called after initialization - not thread safe
void
notifications_put(device_notification_t id, TaskHandle_t h_task);

#endif
