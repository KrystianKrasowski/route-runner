#include "task_manual_control.hpp"
#include "FreeRTOS.h"
#include "linebot/api.hpp"
#include "linebot/domain/commands.hpp"
#include "mapper/dualshock2_commands.hpp"
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
            uint16_t          raw_control    = dualshock2_.read();
            linebot::commands remote_control = mapper::map(raw_control);

            api_.attempt_mode_switch(remote_control);
            api_.attempt_maneuver(remote_control);
        }
    }
}

} // namespace app
