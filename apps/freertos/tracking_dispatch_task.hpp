#pragma once

#include "FreeRTOS.h"
#include "device/qtrhd06a.hpp"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class tracking_dispatch_task
    : public task_base<tracking_dispatch_task, TASK_MEM_TRACKING_DISPATCH>
{
public:

    static tracking_dispatch_task&
    of(device::qtrhd06a&  qtrhd06a,
       linebot::api&      api,
       EventGroupHandle_t event_group);

    void
    run();

    tracking_dispatch_task(tracking_dispatch_task& other) = delete;

    tracking_dispatch_task&
    operator=(tracking_dispatch_task& other) = delete;

    tracking_dispatch_task&&
    operator=(tracking_dispatch_task&& other) = delete;

private:

    device::qtrhd06a&  qtrhd06a_;
    linebot::api&      api_;
    EventGroupHandle_t event_group_;

    tracking_dispatch_task(
        device::qtrhd06a&  qtrhd06a,
        linebot::api&      api,
        EventGroupHandle_t event_group
    )
        : task_base{"trdsp", 3},
          qtrhd06a_{qtrhd06a},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app
