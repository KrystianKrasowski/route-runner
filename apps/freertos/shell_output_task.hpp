#pragma once

#include "device/shell.hpp"
#include "stream_buffer.hpp"
#include "task_base.hpp"

namespace app
{

class shell_output_task : public task_base<shell_output_task, 56>
{
public:

    static shell_output_task&
    of(device::shell& shell, shell_stream& stream_buffer);

    void
    run();

private:

    device::shell& shell_;
    shell_stream&  stream_buffer_;

    shell_output_task(device::shell& shell, shell_stream& stream_buffer)
        : task_base{"shout", 1},
          shell_{shell},
          stream_buffer_{stream_buffer}
    {
    }
};

} // namespace app
