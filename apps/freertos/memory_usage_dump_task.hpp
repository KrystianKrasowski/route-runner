#pragma once

#include "config.h"
#include "shell_command_task.hpp"
#include "stream_buffer.hpp"
#include "task_base.hpp"

namespace app
{

class memory_usage_dump_task
    : public task_base<memory_usage_dump_task, TASK_MEM_USAGE_DUMP>
{
public:

    static memory_usage_dump_task&
    of(const shell_stream& shell_stream, const event_group& event_group);

    void
    run();

private:

    const shell_stream& shell_stream_;
    const event_group&  event_group_;

    memory_usage_dump_task(
        const shell_stream& shell_stream, const event_group& event_group
    )
        : task_base{"memdmp", 1},
          shell_stream_{shell_stream},
          event_group_{event_group}
    {
    }
};

} // namespace app
