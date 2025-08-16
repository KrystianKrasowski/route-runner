#ifndef _APPLICATION_TASK_MANUAL_CONTROL_H
#define _APPLICATION_TASK_MANUAL_CONTROL_H

#include "FreeRTOS.h"
#include "device/dualshock2.hpp"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class manual_dispatch_task
    : public task_base<manual_dispatch_task, TASK_MEM_MANUAL_DISPATCH>
{
public:

    static manual_dispatch_task&
    of(device::dualshock2& dualshock2,
       linebot::api&       api,
       EventGroupHandle_t  event_group);

    void
    run();

    manual_dispatch_task(manual_dispatch_task& other) = delete;

    manual_dispatch_task&
    operator=(manual_dispatch_task& other) = delete;

    manual_dispatch_task&&
    operator=(manual_dispatch_task&& other) = delete;

private:

    device::dualshock2& dualshock2_;
    linebot::api&       api_;
    EventGroupHandle_t  event_group_;

    manual_dispatch_task(
        device::dualshock2& dualshock2,
        linebot::api&       api,
        EventGroupHandle_t  event_group
    )
        : task_base{"mndsp", 2},
          dualshock2_{dualshock2},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app

#endif
