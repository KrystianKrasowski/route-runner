#include "application.h"
#include "devices/devices.h"
#include "devices/port.h"
#include "notifications.h"
#include "pathbot/store.h"
#include "task_domain_dump.h"
#include "task_immediate_stop.h"
#include "task_manual_control.h"
#include "task_route_tracking.h"

int
main()
{
    devices_init();
    pathbot_store_init(NULL);
    notifications_init();

    auto& task_manual_control = app::task_manual_control::of();
    auto& task_route_tracking = app::task_route_tracking::of();
    auto& task_immediate_stop = app::task_immediate_stop::of();
    auto& task_domain_dump    = app::task_domain_dump::of();

    auto h_task_manual_control = task_manual_control.register_rtos_task();
    auto h_task_route_tracking = task_route_tracking.register_rtos_task();
    auto h_task_immediate_stop = task_immediate_stop.register_rtos_task();
    auto h_task_domain_dump    = task_domain_dump.register_rtos_task();

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
