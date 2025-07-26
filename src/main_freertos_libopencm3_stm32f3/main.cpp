#include "FreeRTOS.h"
#include "device/isr_event_emitter.hpp"
#include "device/tree.hpp"
#include "isr_event_emitter_adapter.hpp"
#include "linebot/data_store.hpp"
#include "task.h"
#include "task_factory.hpp"
#include "task_immediate_stop.hpp"
#include "task_manual_control.hpp"
#include "task_route_tracking.hpp"
#include <etl/utility.h>

linebot::data_store            store;
app::isr_event_emitter_adapter events;

int
main()
{
    auto devices = device::tree::of(events);

    app::task_factory task_factory{devices, store};

    auto& manual_control_task = task_factory.create_manual_control_task();
    auto& route_tracking_task = task_factory.create_route_tracking_task();
    auto& immediate_stop_task = task_factory.create_immediate_stop_task();
    auto& shell_command_dispatch_task =
        task_factory.create_shell_command_dispatch_task();

    events.register_task_notification(
        device::event_id::DUALSHOCK2_RX_COMPLETE,
        manual_control_task.get_handle()
    );

    events.register_task_notification(
        device::event_id::QTRHD06A_CONVERSION_COMPLETE,
        route_tracking_task.get_handle()
    );

    events.register_task_notification(
        device::event_id::TIMEOUT, immediate_stop_task.get_handle()
    );

    events.register_task_notification(
        device::event_id::SHELL_COMMANDED,
        shell_command_dispatch_task.get_handle()
    );

    vTaskStartScheduler();

    // trap here in case of the scheduler error
    while (1)
    {
    }
}
