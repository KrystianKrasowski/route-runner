#pragma once

#include "FreeRTOS.h"
#include "device/isr_event_emitter.hpp"
#include "task.h"
#include <etl/optional.h>

namespace app
{

class isr_event_emitter_adapter : public device::isr_event_emitter
{
public:

    isr_event_emitter_adapter(
        TaskHandle_t& task_manual_control, TaskHandle_t& task_route_tracking
    )
        : task_manual_control_{task_manual_control},
          task_route_tracking_{task_route_tracking}
    {
    }

    void
    enable()
    {
        enabled = true;
    }

    void
    emit(device::event_id event) override
    {
        auto maybe_task = get_task(event);

        if (enabled && maybe_task.has_value())
        {
            auto task                       = maybe_task.value();
            auto higher_priority_task_woken = pdFALSE;

            vTaskNotifyGiveFromISR(task, &higher_priority_task_woken);
            portYIELD_FROM_ISR(higher_priority_task_woken);
        }
    }

private:

    bool          enabled = false;
    TaskHandle_t& task_manual_control_;
    TaskHandle_t& task_route_tracking_;

    etl::optional<TaskHandle_t>
    get_task(device::event_id event)
    {
        switch (event)
        {
        case device::event_id::DUALSHOCK2_RX_COMPLETE:
            return etl::optional{task_manual_control_};

        case device::event_id::QTRHD06A_CONVERSION_COMPLETE:
            return etl::optional{task_route_tracking_};

        default:
            return etl::nullopt;
        }
    }
};

} // namespace app
