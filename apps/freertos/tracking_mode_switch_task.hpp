#pragma once

#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class tracking_mode_switch_task
    : public task_base<tracking_mode_switch_task, 48>
{
public:

    static tracking_mode_switch_task&
    of(linebot::api& api, EventGroupHandle_t event_group);

    void
    run();

    tracking_mode_switch_task(tracking_mode_switch_task& other) = delete;

    tracking_mode_switch_task&
    operator=(tracking_mode_switch_task& other) = delete;

    tracking_mode_switch_task&&
    operator=(tracking_mode_switch_task&& other) = delete;

private:

    linebot::api&      api_;
    EventGroupHandle_t event_group_;

    tracking_mode_switch_task(linebot::api& api, EventGroupHandle_t event_group)
        : task_base{"tracking_mode", 2},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app
