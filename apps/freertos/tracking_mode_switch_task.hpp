#pragma once

#include "FreeRTOS.h"
#include "event_group.hpp"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class tracking_mode_switch_task
    : public task_base<tracking_mode_switch_task, TASK_MEM_TRACKING_MODE_SWITCH>
{
public:

    static tracking_mode_switch_task&
    of(const event_group& event_group, linebot::api& api);

    void
    run();

    tracking_mode_switch_task(const tracking_mode_switch_task& other) = delete;

    tracking_mode_switch_task(tracking_mode_switch_task&& other) = delete;

    tracking_mode_switch_task&
    operator=(const tracking_mode_switch_task& other) = delete;

    tracking_mode_switch_task&
    operator=(tracking_mode_switch_task&& other) = delete;

private:

    const event_group& event_group_;
    linebot::api&      api_;

    tracking_mode_switch_task(const event_group& event_group, linebot::api& api)
        : task_base{"trmds", 2},
          event_group_{event_group},
          api_{api}
    {
    }
};

} // namespace app
