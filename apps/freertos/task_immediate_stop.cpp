#include "FreeRTOS.h"
#include "task_immediate_stop.hpp"
#include <cstdint>

namespace app
{

task_immediate_stop&
task_immediate_stop::of(linebot::api& api)
{
    static task_immediate_stop task{api};
    return task;
}

void
task_immediate_stop::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000));

        if (count)
        {
            api_.halt();
        }
    }
}

} // namespace app
