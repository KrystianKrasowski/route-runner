#pragma once

#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class task_manual_motion : public task_base<task_manual_motion, 32>
{
public:

    static task_manual_motion&
    of(linebot::api& api, EventGroupHandle_t event_group);

    void
    run();

private:

    linebot::api&      api_;
    EventGroupHandle_t event_group_;

    task_manual_motion(linebot::api& api, EventGroupHandle_t event_group)
        : task_base("manual motion", 2),
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app
