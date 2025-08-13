#include "domain_dump_task.hpp"
#include "FreeRTOS.h"
#include "shell_command_task.hpp"

namespace app
{

domain_dump_task&
domain_dump_task::of(
    linebot::api&      api,
    EventGroupHandle_t event_group,
    shell_stream&      shell_stream
)
{
    static domain_dump_task task{api, event_group, shell_stream};
    return task;
}

void
domain_dump_task::run()
{
    while (1)
    {
        EventBits_t wait_for = shell_command_task::DOMAIN_DUMP_BIT;

        EventBits_t bits = xEventGroupWaitBits(
            event_group_, wait_for, pdTRUE, pdTRUE, pdMS_TO_TICKS(1000)
        );

        if ((bits & wait_for) != 0)
        {
            linebot::info_string info = "";
            api_.dump_store(info);
            shell_stream_.send(info);
        }
    }
}

} // namespace app
