#ifndef _MAIN_FREERTOS_NOTIFICATIONS_PORT_H
#define _MAIN_FREERTOS_NOTIFICATIONS_PORT_H

#include "FreeRTOS.h"
#include "task.h"

void
notifications_init(void);

void
notifications_set_dualshock2_task(TaskHandle_t h_task);

void
notifications_set_route_convertions_task(TaskHandle_t h_task);

void
notifications_set_route_guard_task(TaskHandle_t h_task);

void
notifications_set_serial_request_task(TaskHandle_t h_task);

#endif
