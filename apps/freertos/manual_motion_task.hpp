#pragma once

#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class manual_motion_task
    : public task_base<manual_motion_task, TASK_MEM_MANUAL_MOTION>
{
public:

    static manual_motion_task&
    of(linebot::api& api, EventGroupHandle_t event_group);

    void
    run();

    manual_motion_task(manual_motion_task& other) = delete;

    manual_motion_task&
    operator=(manual_motion_task& other) = delete;

    manual_motion_task&&
    operator=(manual_motion_task&& other) = delete;

private:

    linebot::api&      api_;
    EventGroupHandle_t event_group_;

    manual_motion_task(linebot::api& api, EventGroupHandle_t event_group)
        : task_base{"mnmot", 2},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app
