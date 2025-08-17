#include "domain_dump_task.hpp"
#include "FreeRTOS.h"
#include "shell_command_task.hpp"

namespace app
{

domain_dump_task&
domain_dump_task::of(
    const shell_stream& shell_stream,
    const event_group&  event_group,
    linebot::api&       api
)
{
    static domain_dump_task task{shell_stream, event_group, api};
    return task;
}

void
domain_dump_task::run()
{
    while (1)
    {
        EventBits_t wait_for = shell_command_task::DOMAIN_DUMP_BIT;
        EventBits_t bits = event_group_.wait_bits(wait_for, true, true, 1000);

        if ((bits & wait_for) != 0)
        {
            linebot::info_string info = "";
            api_.dump_store(info);
            shell_stream_.send(info);
        }
    }
}

} // namespace app
