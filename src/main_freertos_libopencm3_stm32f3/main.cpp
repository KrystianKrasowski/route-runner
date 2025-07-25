#include "FreeRTOS.h"
#include "adapter/motion_l293.hpp"
#include "adapter/route_guard_timeout.hpp"
#include "adapter/status_indicator_toggle_sequence.hpp"
#include "device/isr_event_emitter.hpp"
#include "device/tree.hpp"
#include "isr_event_emitter_adapter.hpp"
#include "linebot/data_store.hpp"
#include "task.h"
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

    // TODO: introduce task factory

    auto& motion =
        adapter::motion_l293::of(devices.motor_left_, devices.motor_right_);

    auto& status_indicator =
        adapter::status_indicator_toggle_sequence::of(devices.blink_);

    auto& route_guard =
        adapter::route_guard_timeout::of(devices.offroute_timeout_);

    auto& api = linebot::api::of(store, motion, status_indicator, route_guard);

    auto& task_manual_control =
        app::task_manual_control::of(devices.remote_control_, api);

    auto& task_route_tracking =
        app::task_route_tracking::of(devices.line_sensor_, api);

    auto& task_immediate_stop = app::task_immediate_stop::of(api);

    auto h_task_manual_control = task_manual_control.register_rtos_task();
    auto h_task_route_tracking = task_route_tracking.register_rtos_task();
    auto h_task_immediate_stop = task_immediate_stop.register_rtos_task();

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
