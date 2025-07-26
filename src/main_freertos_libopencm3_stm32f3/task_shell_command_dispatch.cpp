#include "task_shell_command_dispatch.hpp"
#include "device/toggle_sequence.hpp"
#include "projdefs.h"
#include "task_base.hpp"
#include <cstdint>

namespace app
{

task_shell_command_dispatch&
task_shell_command_dispatch::of(device::toggle_sequence& blink)
{
    static task_shell_command_dispatch task{blink};
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
            blink_.change_sequence(0xb);
        }
    }
}

} // namespace app
