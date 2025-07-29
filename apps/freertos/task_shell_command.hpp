#pragma once

#include "FreeRTOS.h"
#include "device/shell.hpp"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"
#include <cstdint>

namespace app
{

class task_shell_command : public task_base<task_shell_command, 64>
{
public:

    static constexpr uint8_t DOMAIN_DUMP_BIT = 0x1;

    static task_shell_command&
    of(device::shell& shell, linebot::api& api, EventGroupHandle_t event_group);

    void
    run();

private:

    device::shell&     shell_;
    linebot::api&      api_;
    EventGroupHandle_t event_group_;

    // TODO: Task names should be passed by their consturctor - we can have
    // multiple instances of one derived task
    task_shell_command(
        device::shell& shell, linebot::api& api, EventGroupHandle_t event_group
    )
        : task_base("shell disp", 1),
          shell_{shell},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app
