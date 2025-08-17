#pragma once

#include "FreeRTOS.h"
#include "event_group.hpp"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class tracking_motion_task
    : public task_base<tracking_motion_task, TASK_MEM_TRACKING_MOTION>
{
public:

    static tracking_motion_task&
    of(const event_group& event_group, linebot::api& api);

    void
    run();

    tracking_motion_task(const tracking_motion_task& other) = delete;

    tracking_motion_task(tracking_motion_task&& other) = delete;

    tracking_motion_task&
    operator=(const tracking_motion_task& other) = delete;

    tracking_motion_task&
    operator=(tracking_motion_task&& other) = delete;

private:

    const event_group& even_group_;
    linebot::api&      api_;

    tracking_motion_task(const event_group& event_groups, linebot::api& api)
        : task_base{"trmot", 2},
          even_group_{event_groups},
          api_{api}
    {
    }
};

} // namespace app
