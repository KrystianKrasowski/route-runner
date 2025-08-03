#include "task_manual_control.hpp"
#include "FreeRTOS.h"
#include "linebot/api.hpp"
#include "linebot/domain/motion_control.hpp"
#include "mapper/dualshock2_mode_control.hpp"
#include "mapper/dualshock2_motion_control.hpp"
#include "mapper/dualshock2_pid_control.hpp"
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
            auto raw_control    = dualshock2_.read();
            auto motion_control = mapper::map_motion_control(raw_control);
            auto mode_control   = mapper::map_mode_control(raw_control);
            auto pid_control    = mapper::map_pid_control(raw_control);

            api_.attempt_maneuver(motion_control);
            api_.attempt_mode_switch(mode_control);
            api_.tune_pid_regulator(pid_control);
        }
    }
}

} // namespace app
