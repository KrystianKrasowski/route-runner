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
    device::dualshock2& dualshock2,
    linebot::api&       api,
    EventGroupHandle_t  event_group
)
{
    static manual_dispatch_task task{dualshock2, api, event_group};
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

            xEventGroupSetBits(event_group_, actions.as_uint());
        }
    }
}

} // namespace app
