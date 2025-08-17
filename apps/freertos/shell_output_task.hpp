#pragma once

#include "device/shell.hpp"
#include "mutex.hpp"
#include "stream_buffer.hpp"
#include "task_base.hpp"

namespace app
{

class shell_output_task
    : public task_base<shell_output_task, TASK_MEM_SHELL_OUTPUT>
{
public:

    static shell_output_task&
    of(device::shell& shell, shell_stream& stream_buffer, mutex& mutex);

    void
    run();

    shell_output_task(const shell_output_task& other) = delete;

    shell_output_task(shell_output_task&& other) = delete;

    shell_output_task&
    operator=(const shell_output_task& other) = delete;

    shell_output_task&
    operator=(shell_output_task&& other) = delete;

private:

    static constexpr uint16_t TIMEOUT_MS = 1000;

    device::shell& shell_;
    shell_stream&  stream_buffer_;
    mutex&         mutex_;

    shell_output_task(
        device::shell& shell, shell_stream& stream_buffer, mutex& mutex
    )
        : task_base{"shout", 1},
          shell_{shell},
          stream_buffer_{stream_buffer},
          mutex_{mutex}
    {
    }
};

} // namespace app
