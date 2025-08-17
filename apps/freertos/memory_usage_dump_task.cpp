#include "memory_usage_dump_task.hpp"

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
memory_usage_dump_task::run()
{
    while (1)
    {
        EventBits_t wait_for = shell_command_task::TASK_MEM_USE_BIT;
        EventBits_t bits = event_group_.wait_bits(wait_for, true, true, 1000);

        if ((bits & wait_for) != 0)
        {
            etl::string<7> msg = "hello\n\r";
            shell_stream_.send(msg);
        }
    }
}

} // namespace app
