#ifndef _APPLICATION_TASK_MANUAL_CONTROL_H
#define _APPLICATION_TASK_MANUAL_CONTROL_H

#include "FreeRTOS.h"
#include "device/dualshock2.hpp"
#include "event_group.hpp"
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
    of(const event_group&  event_group,
       device::dualshock2& dualshock2,
       linebot::api&       api);

    void
    run();

    manual_dispatch_task(manual_dispatch_task& other) = delete;

    manual_dispatch_task&
    operator=(manual_dispatch_task& other) = delete;

    manual_dispatch_task&&
    operator=(manual_dispatch_task&& other) = delete;

private:

    const event_group&  event_group_;
    device::dualshock2& dualshock2_;
    linebot::api&       api_;

    manual_dispatch_task(
        const event_group&  event_group,
        device::dualshock2& dualshock2,
        linebot::api&       api
    )
        : task_base{"mndsp", 2},
          event_group_{event_group},
          dualshock2_{dualshock2},
          api_{api}
    {
    }
};

} // namespace app

#endif
