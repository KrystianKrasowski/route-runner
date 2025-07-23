#include "task_route_tracking.hpp"
#include "FreeRTOS.h"
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

        }
    }
}

} // namespace app
