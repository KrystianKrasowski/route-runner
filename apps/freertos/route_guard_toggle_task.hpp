#pragma once

#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class route_guard_toggle_task
    : public task_base<route_guard_toggle_task, TASK_MEM_ROUTE_GUARD_TOGGLE>
{
public:

    static route_guard_toggle_task&
    of(linebot::api& api, EventGroupHandle_t event_group);

    void
    run();

    route_guard_toggle_task(route_guard_toggle_task& other) = delete;

    route_guard_toggle_task&
    operator=(route_guard_toggle_task& other) = delete;

    route_guard_toggle_task&&
    operator=(route_guard_toggle_task&& other) = delete;

private:

    linebot::api&      api_;
    EventGroupHandle_t event_group_;

    route_guard_toggle_task(linebot::api& api, EventGroupHandle_t event_group)
        : task_base{"rtgrd", 3},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app
