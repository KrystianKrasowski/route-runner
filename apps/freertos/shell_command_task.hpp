#pragma once

#include "FreeRTOS.h"
#include "device/shell.hpp"
#include "event_group.hpp"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"
#include <cstdint>

namespace app
{

class shell_command_task
    : public task_base<shell_command_task, TASK_MEM_SHELL_COMMAND>
{
public:

    static constexpr uint8_t DOMAIN_DUMP_BIT  = 0x1;
    static constexpr uint8_t TASK_MEM_USE_BIT = 0x2;

    static shell_command_task&
    of(const event_group& event_group, device::shell& shell, linebot::api& api);

    void
    run();

private:

    const event_group& event_group_;
    device::shell&     shell_;
    linebot::api&      api_;

    // TODO: Task names should be passed by their consturctor - we can have
    // multiple instances of one derived task
    shell_command_task(
        const event_group& event_group, device::shell& shell, linebot::api& api
    )
        : task_base("shcmd", 1),
          event_group_{event_group},
          shell_{shell},
          api_{api}
    {
    }
};

} // namespace app
