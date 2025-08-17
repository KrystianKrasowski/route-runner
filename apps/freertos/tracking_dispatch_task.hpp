#pragma once

#include "FreeRTOS.h"
#include "device/qtrhd06a.hpp"
#include "event_group.hpp"
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
    of(const device::qtrhd06a& qtrhd06a,
       const event_group&      event_group,
       linebot::api&           api);

    void
    run();

    tracking_dispatch_task(const tracking_dispatch_task& other) = delete;

    tracking_dispatch_task(tracking_dispatch_task&& other) = delete;

    tracking_dispatch_task&
    operator=(const tracking_dispatch_task& other) = delete;

    tracking_dispatch_task&
    operator=(tracking_dispatch_task&& other) = delete;

private:

    const device::qtrhd06a& qtrhd06a_;
    const event_group&      event_group_;
    linebot::api&           api_;

    tracking_dispatch_task(
        const device::qtrhd06a& qtrhd06a,
        const event_group&      event_group,
        linebot::api&           api
    )
        : task_base{"trdsp", 3},
          qtrhd06a_{qtrhd06a},
          event_group_{event_group},
          api_{api}
    {
    }
};

} // namespace app
