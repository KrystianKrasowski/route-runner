#include "task_route_tracking.hpp"
#include "FreeRTOS.h"
#include "mapper/qtrhd06a_coordinates.hpp"
#include "task_base.hpp"
#include <cstdint>

namespace app
{

task_route_tracking&
task_route_tracking::of(device::qtrhd06a& line_sensor, linebot::api& api)
{
    static task_route_tracking task{line_sensor, api};
    return task;
}

void
task_route_tracking::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(5));

        if (count)
        {
            auto raw_values  = line_sensor_.read();
            auto line_position = mapper::map(raw_values);

            api_.attempt_route_guard_toggle(line_position);
            api_.attempt_mode_switch(line_position);
        }
    }
}

} // namespace app
