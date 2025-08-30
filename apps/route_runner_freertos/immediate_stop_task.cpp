#include "FreeRTOS.h"
#include "immediate_stop_task.hpp"
#include <cstdint>

namespace app
{

immediate_stop_task&
immediate_stop_task::of(linebot::api& api)
{
    static immediate_stop_task task{api};
    return task;
}

void
immediate_stop_task::run()
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
