#pragma once

#include "config.h"
#include "event_group.hpp"
#include "stream_buffer.hpp"
#include "task_base.hpp"
#include <etl/vector.h>

namespace app
{

class memory_usage_dump_task
    : public task_base<memory_usage_dump_task, TASK_MEM_USAGE_DUMP>
{
public:

    static memory_usage_dump_task&
    of(const shell_stream& shell_stream, const event_group& event_group);

    void
    monitor(task_info task);

    void
    run();

    memory_usage_dump_task(const memory_usage_dump_task& other) = delete;

    memory_usage_dump_task(memory_usage_dump_task&& other) = delete;

    memory_usage_dump_task&
    operator=(const memory_usage_dump_task& other) = delete;

    memory_usage_dump_task&
    operator=(memory_usage_dump_task&& other) = delete;

private:

    static constexpr uint8_t MONITORED_TASKS_LENGTH = 13;

    // MONITORED_TASKS_LENGTH x (MAX_TASK_NAME + 16)
    static constexpr uint16_t MESSAGE_LENGTH = 416;

    using message_string = etl::string<MESSAGE_LENGTH>;

    const shell_stream& shell_stream_;
    const event_group&  event_group_;

    etl::vector<task_info, MONITORED_TASKS_LENGTH> monitored_tasks_;

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
