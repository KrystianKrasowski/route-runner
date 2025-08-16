#pragma once

#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class manual_mode_switch_task
    : public task_base<manual_mode_switch_task, TASK_MEM_MANUAL_MODE_SWITCH>
{
public:

    static manual_mode_switch_task&
    of(linebot::api& api, EventGroupHandle_t event_group);

    void
    run();

    manual_mode_switch_task(manual_mode_switch_task& other) = delete;

    manual_mode_switch_task&
    operator=(manual_mode_switch_task& other) = delete;

    manual_mode_switch_task&&
    operator=(manual_mode_switch_task&& other) = delete;

private:

    linebot::api&      api_;
    EventGroupHandle_t event_group_;

    manual_mode_switch_task(linebot::api& api, EventGroupHandle_t event_group)
        : task_base{"mnmds", 2},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app
