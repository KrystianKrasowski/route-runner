#pragma once

#include "FreeRTOS.h"
#include "device/isr_event_emitter.hpp"
#include "task.h"
#include <etl/map.h>
#include <etl/unordered_map.h>

namespace app
{

class isr_event_emitter_adapter : public device::isr_event_emitter
{
public:

    void
    emit(device::event_id event) override;

    void
    register_task_notification(device::event_id event, TaskHandle_t task);

private:

    etl::unordered_map<device::event_id, TaskHandle_t, 4>
        rtos_notifications_map_;
};

} // namespace app
