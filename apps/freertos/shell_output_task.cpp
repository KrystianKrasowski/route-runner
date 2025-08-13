#include "shell_output_task.hpp"

namespace app
{

shell_output_task&
shell_output_task::of(device::shell& shell, shell_stream& stream_buffer)
{
    static shell_output_task task{shell, stream_buffer};
    return task;
}

void
shell_output_task::run()
{
    // TODO: Extract this magic number
    char   buffer[128];
    size_t received_bytes;

    while (1)
    {
        received_bytes = stream_buffer_.receive(buffer, sizeof(buffer));

        if (received_bytes > 0)
        {
            shell_.send(buffer, received_bytes);
        }
    }
}

} // namespace app
