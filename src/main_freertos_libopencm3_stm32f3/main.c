#include "FreeRTOS.h"
#include "application.h"
#include "notifications.h"
#include "task.h"
#include <devices/devices.h>
#include <pathbot/store.h>
#include <stddef.h>
#include <stdint.h>

TaskHandle_t h_task_manual_control;
TaskHandle_t h_task_route_tracking;
TaskHandle_t h_task_immediate_stop;
TaskHandle_t h_task_domain_dump;

int
main(void)
{
    devices_init();
    pathbot_store_init(NULL);
    notifications_init();

    (void)xTaskCreate(app_handle_manual_control,
                      "task manual",
                      48,
                      NULL,
                      2,
                      &h_task_manual_control);

    (void)xTaskCreate(app_handle_route_tracking,
                      "task tracking",
                      128,
                      NULL,
                      2,
                      &h_task_route_tracking);

    (void)xTaskCreate(app_handle_immediate_stop,
                      "task route guard",
                      48,
                      NULL,
                      3,
                      &h_task_immediate_stop);

    (void)xTaskCreate(app_handle_domain_dump,
                      "task domain dump",
                      256,
                      NULL,
                      1,
                      &h_task_domain_dump);

    notifications_set_dualshock2_task(h_task_manual_control);
    notifications_set_route_convertions_task(h_task_route_tracking);
    notifications_set_route_guard_task(h_task_immediate_stop);
    notifications_set_serial_request_task(h_task_domain_dump);

    vTaskStartScheduler();

    while (1)
    {
        // should never reach here
    }
}
