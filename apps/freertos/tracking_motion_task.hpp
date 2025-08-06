#pragma once

#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class tracking_motion_task : public task_base<tracking_motion_task, 40>
{
public:

    static tracking_motion_task&
    of(linebot::api& api, EventGroupHandle_t event_group);

    void
    run();

    tracking_motion_task(tracking_motion_task& other) = delete;

    tracking_motion_task&
    operator=(tracking_motion_task& other) = delete;

    tracking_motion_task&&
    operator=(tracking_motion_task&& other) = delete;

private:

    linebot::api&      api_;
    EventGroupHandle_t even_group_;

    tracking_motion_task(linebot::api& api, EventGroupHandle_t event_groups)
        : task_base{"tracking_motion", 2},
          api_{api},
          even_group_{event_groups}
    {
    }
};

} // namespace app
