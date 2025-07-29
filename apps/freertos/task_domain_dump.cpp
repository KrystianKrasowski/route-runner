#include "task_domain_dump.hpp"
#include "FreeRTOS.h"
#include "projdefs.h"
#include "task_shell_command.hpp"

namespace app
{

task_domain_dump&
task_domain_dump::of(linebot::api& api, EventGroupHandle_t event_group)
{
    static task_domain_dump task{api, event_group};
    return task;
}

void
task_domain_dump::run()
{
    while (1)
    {
        EventBits_t wait_for = task_shell_command::DOMAIN_DUMP_BIT;

        EventBits_t bits = xEventGroupWaitBits(
            event_group_, wait_for, pdTRUE, pdTRUE, pdMS_TO_TICKS(1000)
        );

        if ((bits & wait_for) != 0)
        {
            api_.dump_store();
        }
    }
}

} // namespace app
