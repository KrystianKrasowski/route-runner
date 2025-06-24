#include "FreeRTOS.h"
#include "notifications.h"
#include <devices/port.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef struct
{
    TaskHandle_t h_dualshock2_task;
    TaskHandle_t h_route_convertions_task;
    TaskHandle_t h_route_guard_task;
    TaskHandle_t h_serial_request_task;
} notifications_config_t;

static notifications_config_t config;

void
notifications_init(void)
{
    memset(&config, 0, sizeof(config));
}

void
notifications_set_dualshock2_task(TaskHandle_t h_task)
{
    config.h_dualshock2_task = h_task;
}

void
notifications_set_route_convertions_task(TaskHandle_t h_task)
{
    config.h_route_convertions_task = h_task;
}

void
notifications_set_route_guard_task(TaskHandle_t h_task)
{
    config.h_route_guard_task = h_task;
}

void
notifications_set_serial_request_task(TaskHandle_t h_task)
{
    config.h_serial_request_task = h_task;
}

void
devices_port_notification_give(device_notification_t id)
{
    BaseType_t   higher_priority_task_woken = pdFALSE;
    TaskHandle_t h_task                     = NULL;

    switch (id)
    {
        case DEVICE_NOTIFICATION_ROUTE_CONVERTIONS:
            h_task = config.h_route_convertions_task;
            break;

        case DEVICE_NOTIFICATION_TIMEOUT_GUARD_ROUTE:
            h_task = config.h_route_guard_task;
            break;

        case DEVICE_NOTIFICATION_SERIAL_REQUEST:
            h_task = config.h_serial_request_task;
            break;

        default:
        case DEVICE_NOTIFICATION_DUALSHOCK2:
            h_task = config.h_dualshock2_task;
            break;
    }

    if (NULL != h_task)
    {
        vTaskNotifyGiveFromISR(h_task, &higher_priority_task_woken);
        portYIELD_FROM_ISR(higher_priority_task_woken);
    }
}
