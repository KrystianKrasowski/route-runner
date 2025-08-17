#pragma once

#include "FreeRTOS.h"
#include "event_group.hpp"
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
    of(const event_group& event_group, linebot::api& api);

    void
    run();

    manual_mode_switch_task(manual_mode_switch_task& other) = delete;

    manual_mode_switch_task&
    operator=(manual_mode_switch_task& other) = delete;

    manual_mode_switch_task&&
    operator=(manual_mode_switch_task&& other) = delete;

private:

    const event_group& event_group_;
    linebot::api&      api_;

    manual_mode_switch_task(const event_group& event_group, linebot::api& api)
        : task_base{"mnmds", 2},
          event_group_{event_group},
          api_{api}
    {
    }
};

} // namespace app
