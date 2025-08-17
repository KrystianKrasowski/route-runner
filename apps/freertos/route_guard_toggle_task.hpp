#pragma once

#include "FreeRTOS.h"
#include "event_group.hpp"
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
    of(const event_group& event_group, linebot::api& api);

    void
    run();

    route_guard_toggle_task(route_guard_toggle_task& other) = delete;

    route_guard_toggle_task&
    operator=(route_guard_toggle_task& other) = delete;

    route_guard_toggle_task&&
    operator=(route_guard_toggle_task&& other) = delete;

private:

    const event_group& event_group_;
    linebot::api&      api_;

    route_guard_toggle_task(const event_group& event_group, linebot::api& api)
        : task_base{"rtgrd", 3},
          event_group_{event_group},
          api_{api}
    {
    }
};

} // namespace app
