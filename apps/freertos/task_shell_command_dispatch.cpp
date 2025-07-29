#include "task_shell_command_dispatch.hpp"
#include "FreeRTOS.h"
#include "linebot/api.hpp"
#include "task_base.hpp"
#include <cstdint>
#include <etl/string.h>

namespace app
{

task_shell_command_dispatch&
task_shell_command_dispatch::of(device::shell& shell, linebot::api& api)
{
    static task_shell_command_dispatch task{shell, api};
    return task;
}

void
task_shell_command_dispatch::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000));

        if (count)
        {
            api_.dump_store();
        }
    }
}

} // namespace app
