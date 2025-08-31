#include "isr_event_emitter_adapter.hpp"
#include "FreeRTOS.h"
#include "device/isr_event_emitter.hpp"
#include "task.h"
#include <etl/map.h>

namespace app
{

void
isr_event_emitter_adapter::emit(device::event_id event)
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
isr_event_emitter_adapter::register_task_notification(
    device::event_id event, TaskHandle_t task
)
{
    if (!rtos_notifications_map_.full()
        || rtos_notifications_map_.contains(event))
    {
        rtos_notifications_map_[event] = task;
    }
}

} // namespace app
