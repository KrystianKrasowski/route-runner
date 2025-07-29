#include "task_shell_command.hpp"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include <cstdint>
#include <etl/string.h>

namespace app
{

task_shell_command&
task_shell_command::of(
    device::shell& shell, linebot::api& api, EventGroupHandle_t event_group
)
{
    static task_shell_command task{shell, api, event_group};
    return task;
}

void
task_shell_command::run()
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
            }

            if (bits != 0)
            {
                xEventGroupSetBits(event_group_, DOMAIN_DUMP_BIT);
            }
        }
    }
}

} // namespace app
