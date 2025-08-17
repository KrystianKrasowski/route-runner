#pragma once

#include "FreeRTOS.h"
#include "event_group.hpp"
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
    of(const event_group& event_group, linebot::api& api);

    void
    run();

    manual_motion_task(manual_motion_task& other) = delete;

    manual_motion_task&
    operator=(manual_motion_task& other) = delete;

    manual_motion_task&&
    operator=(manual_motion_task&& other) = delete;

private:

    const event_group& event_group_;
    linebot::api&      api_;

    manual_motion_task(const event_group& event_group, linebot::api& api)
        : task_base{"mnmot", 2},
          event_group_{event_group},
          api_{api}
    {
    }
};

} // namespace app
