#include "task_manual_control.hpp"
#include "FreeRTOS.h"
#include "linebot/api.hpp"
#include "linebot/domain/motion_control.hpp"
#include "mapper/dualshock2_motion_control.hpp"
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

            // TODO: Mode should have separate object from motion_control
            // (mode_control?)
            api_.attempt_mode_switch(motion_control);
            api_.attempt_maneuver(motion_control);
        }
    }
}

} // namespace app
