#pragma once

#include "FreeRTOS.h"
#include "device/isr_event_emitter.hpp"
#include "task.h"
#include <etl/map.h>
#include <etl/optional.h>

namespace app
{

class isr_event_emitter_adapter : public device::isr_event_emitter
{
public:

    void
    emit(device::event_id event) override
    {
        if (rtos_notifications_map_.contains(event))
        {
            auto task                  = rtos_notifications_map_[event];
            auto higher_priority_woken = pdFALSE;

            vTaskNotifyGiveFromISR(task, &higher_priority_woken);
            portYIELD_FROM_ISR(higher_priority_woken);
        }
    }

    void
    register_task_notification(device::event_id event, TaskHandle_t task)
    {
        if (!rtos_notifications_map_.full()
            || rtos_notifications_map_.contains(event))
        {
            rtos_notifications_map_[event] = task;
        }
    }

private:

    etl::map<device::event_id, TaskHandle_t, 3> rtos_notifications_map_;
};

} // namespace app
