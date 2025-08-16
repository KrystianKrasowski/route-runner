#pragma once

#include "FreeRTOS.h"
#include "device/shell.hpp"
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
    of(device::shell& shell, linebot::api& api, EventGroupHandle_t event_group);

    void
    run();

private:

    device::shell&     shell_;
    linebot::api&      api_;
    EventGroupHandle_t event_group_;

    // TODO: Task names should be passed by their consturctor - we can have
    // multiple instances of one derived task
    shell_command_task(
        device::shell& shell, linebot::api& api, EventGroupHandle_t event_group
    )
        : task_base("shcmd", 1),
          shell_{shell},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app
