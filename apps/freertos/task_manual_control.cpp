#include "task_manual_control.hpp"
#include "FreeRTOS.h"
#include "linebot/api.hpp"
#include "linebot/domain/actions.hpp"
#include "mapper/dualshock2_remote_control.hpp"
#include "task_base.hpp"
#include <cstdint>

namespace app
{

task_manual_control&
task_manual_control::of(device::dualshock2& dualshock2, linebot::api& api)
{
    static task_manual_control task{dualshock2, api};
    return task;
}

void
task_manual_control::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(20));

        if (count)
        {
            auto raw_control = dualshock2_.read();
            auto commands    = mapper::map_remote_control(raw_control);
            auto actions     = api_.dispatch(commands);

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
