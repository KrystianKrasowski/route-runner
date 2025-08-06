#include "manual_control_dispatch_task.hpp"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "linebot/domain/actions.hpp"
#include "mapper/dualshock2_remote_control.hpp"
#include <cstdint>

namespace app
{

manual_control_dispatch_task&
manual_control_dispatch_task::of(
    device::dualshock2& dualshock2,
    linebot::api&       api,
    EventGroupHandle_t  event_group
)
{
    static manual_control_dispatch_task task{dualshock2, api, event_group};
    return task;
}

void
manual_control_dispatch_task::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(20));

        if (count)
        {
            auto raw_control = dualshock2_.read();
            auto commands    = mapper::map_remote_control(raw_control);
            auto actions     = api_.query(commands);

            xEventGroupSetBits(event_group_, actions.as_uint());

            // TODO: Use event_group to dispatch this
            if (actions.contain(linebot::actions::APPLY_MANEUVER))
            {
                api_.apply_motion_by_remote();
            }

            if (actions.contain(linebot::actions::CHANGE_MODE))
            {
                api_.switch_mode_by_remote();
            }

            if (actions.contain(linebot::actions::TUNE_PID))
            {
                api_.tune_pid_regulator();
            }
        }
    }
}

} // namespace app
