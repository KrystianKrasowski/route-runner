#include "shell_output_task.hpp"

namespace app
{

shell_output_task&
shell_output_task::of(
    device::shell& shell, shell_stream& stream_buffer, mutex& mutex
)
{
    static shell_output_task task{shell, stream_buffer, mutex};
    return task;
}

void
shell_output_task::run()
{
    char buffer[device::shell::MAX_LENGTH];

    while (1)
    {
        size_t received_bytes = stream_buffer_.receive(buffer, sizeof(buffer));

        if (received_bytes > 0 && mutex_.take(TIMEOUT_MS) == pdPASS)
        {
            shell_.send(buffer, received_bytes);
            mutex_.give();
        }
    }
}

} // namespace app
