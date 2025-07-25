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

    devices.blink_.change_sequence(0x1);

    app::task_factory task_factory{devices, store};

    auto& manual_control_task = task_factory.create_manual_control_task();
    auto& route_tracking_task = task_factory.create_route_tracking_task();
    auto& immediate_stop_task = task_factory.create_immediate_stop_task();

    auto h_task_manual_control = manual_control_task.register_rtos_task();
    auto h_task_route_tracking = route_tracking_task.register_rtos_task();
    auto h_task_immediate_stop = immediate_stop_task.register_rtos_task();

    events.register_task_notification(
        device::event_id::DUALSHOCK2_RX_COMPLETE, h_task_manual_control
    );

    events.register_task_notification(
        device::event_id::QTRHD06A_CONVERSION_COMPLETE, h_task_route_tracking
    );

    events.register_task_notification(
        device::event_id::TIMEOUT, h_task_immediate_stop
    );

    vTaskStartScheduler();

    // trap here in case of the scheduler error
    while (1)
    {
    }
}
