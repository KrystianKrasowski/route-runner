#include "memory_usage_dump_task.hpp"
#include "FreeRTOS.h"
#include "shell_command_task.hpp"
#include "task.h"
#include <etl/to_string.h>

namespace app
{

memory_usage_dump_task&
memory_usage_dump_task::of(
    const shell_stream& shell_stream, const event_group& event_group
)
{
    static memory_usage_dump_task task{shell_stream, event_group};
    return task;
}

void
memory_usage_dump_task::monitor(task_info task)
{
    monitored_tasks_.push_back(task);
}

void
memory_usage_dump_task::run()
{
    while (1)
    {
        EventBits_t wait_for = shell_command_task::TASK_MEM_USE_BIT;
        EventBits_t bits = event_group_.wait_bits(wait_for, true, true, 1000);

        if ((bits & wait_for) != 0)
        {
            message_string message = "";

            for (auto task : monitored_tasks_)
            {
                auto watermark = uxTaskGetStackHighWaterMark(task.handle_);

                message += task.name_;
                message += ": ";
                etl::to_string(watermark, message, true);
                message += "\n\r";
            }

            shell_stream_.send(message);
        }
    }
}

} // namespace app
