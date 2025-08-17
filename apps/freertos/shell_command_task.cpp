#include "shell_command_task.hpp"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include <cstdint>
#include <etl/string.h>

namespace app
{

shell_command_task&
shell_command_task::of(
    const event_group& event_group, device::shell& shell, linebot::api& api
)
{
    static shell_command_task task{event_group, shell, api};
    return task;
}

void
shell_command_task::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000));

        if (count)
        {
            EventBits_t bits = 0;

            switch (shell_.read())
            {
            case 'd':
                bits = DOMAIN_DUMP_BIT;
                break;

            case 'm':
                bits = TASK_MEM_USE_BIT;
                break;
            }

            if (bits != 0)
            {
                event_group_.set_bits(bits);
            }
        }
    }
}

} // namespace app
