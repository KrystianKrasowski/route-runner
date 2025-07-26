#pragma once

#include "device/toggle_sequence.hpp"
#include "task_base.hpp"

namespace app
{

class task_shell_command_dispatch
    : public task_base<task_shell_command_dispatch, 48>
{
public:

    static task_shell_command_dispatch&
    of(device::toggle_sequence& blink);

    void
    run();

private:

    device::toggle_sequence& blink_;

    // TODO: Task names should be passed by their consturctor - we can have
    // multiple instances of one derived task
    task_shell_command_dispatch(device::toggle_sequence& blink)
        : task_base("shell disp", 1), blink_{blink}
    {
    }
};

} // namespace app
