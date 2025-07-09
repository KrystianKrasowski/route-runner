#include "FreeRTOS.h"
#include "application.h"
#include "devices/devices.h"
#include "devices/port.h"
#include "notifications.h"
#include "pathbot/store.h"
#include "task.h"
#include "task_immediate_stop.h"
#include "task_manual_control.h"
#include "task_route_tracking.h"

StaticTask_t task_domain_dump_tcb;
StackType_t  task_domain_dump_stack[80];
TaskHandle_t h_task_domain_dump;

int
main()
{
    devices_init();
    pathbot_store_init(NULL);
    notifications_init();

    auto& task_manual_control = app::task_manual_control::of();
    auto& task_route_tracking = app::task_route_tracking::of();
    auto& task_immediate_stop = app::task_immediate_stop::of();

    auto h_task_manual_control = task_manual_control.register_rtos_task();
    auto h_task_route_tracking = task_route_tracking.register_rtos_task();
    auto h_task_immediate_stop = task_immediate_stop.register_rtos_task();

    h_task_domain_dump = xTaskCreateStatic(
        app_handle_domain_dump,
        "task domain dump",
        80,
        NULL,
        1,
        task_domain_dump_stack,
        &task_domain_dump_tcb
    );

    notifications_put(DEVICE_NOTIFICATION_DUALSHOCK2, h_task_manual_control);
    notifications_put(
        DEVICE_NOTIFICATION_ROUTE_CONVERTIONS, h_task_route_tracking
    );
    notifications_put(
        DEVICE_NOTIFICATION_TIMEOUT_GUARD_ROUTE, h_task_immediate_stop
    );
    notifications_put(DEVICE_NOTIFICATION_SERIAL_REQUEST, h_task_domain_dump);

    vTaskStartScheduler();

    // trap here in case of the scheduler error
    while (1)
    {
    }
}
