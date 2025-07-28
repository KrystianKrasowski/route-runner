#pragma once

#include "device/shell.hpp"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class task_shell_command_dispatch
    : public task_base<task_shell_command_dispatch, 144>
{
public:

    static task_shell_command_dispatch&
    of(device::shell& shell, linebot::api& api);

    void
    run();

private:

    device::shell& shell_;
    linebot::api&  api_;

    // TODO: Task names should be passed by their consturctor - we can have
    // multiple instances of one derived task
    task_shell_command_dispatch(device::shell& shell, linebot::api& api)
        : task_base("shell disp", 1),
          shell_{shell},
          api_{api}
    {
    }
};

} // namespace app
