#include "FreeRTOS.h"
#include "adapter/motion_l293.hpp"
#include "adapter/status_indicator_dummy.hpp"
#include "device/tree.hpp"
#include "isr_event_emitter_adapter.hpp"
#include "linebot/data_store.hpp"
#include "task.h"
#include "task_manual_control.hpp"
#include <etl/utility.h>

TaskHandle_t h_task_manual_control;

linebot::data_store store;

app::isr_event_emitter_adapter events{h_task_manual_control};

int
main()
{
    auto devices = device::tree::of(events);

    devices.blink_.change_sequence(0x1);

    auto& motion =
        adapter::motion_l293::of(devices.motor_left_, devices.motor_right_);

    auto& status_indicator = adapter::status_indicator_dummy::of();

    auto& api = linebot::api::of(store, motion, status_indicator);

    auto& task_manual_control =
        app::task_manual_control::of(devices.remote_control_, api);

    h_task_manual_control = task_manual_control.register_rtos_task();

    // TODO: Code smell. Consider event listener registration in task_base
    events.enable();

    vTaskStartScheduler();

    // trap here in case of the scheduler error
    while (1)
    {
    }
}
