#include "manual_dispatch_task.hpp"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "linebot/domain/actions.hpp"
#include "mapper/dualshock2_remote_control.hpp"
#include <cstdint>

namespace app
{

manual_dispatch_task&
manual_dispatch_task::of(
    const event_group&  event_group,
    device::dualshock2& dualshock2,
    linebot::api&       api
)
{
    static manual_dispatch_task task{event_group, dualshock2, api};
    return task;
}

void
manual_dispatch_task::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(20));

        if (count)
        {
            auto raw_control = dualshock2_.read();
            auto actions = api_.query(mapper::map_remote_control(raw_control));

            event_group_.set_bits(actions.as_uint());
        }
    }
}

} // namespace app
