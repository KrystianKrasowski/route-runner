#include "FreeRTOS.h"
#include "devices/dualshock2.h"
#include "mappers/dualshock2_control.h"
#include "pathbot/api.h"
#include "task_base.h"
#include "task_manual_control.h"
#include <etl/pool.h>
#include <stdint.h>
#include <utils/result.h>

namespace app
{

static etl::pool<task_handle_manual_control, 1> pool;

task_handle_manual_control&
task_handle_manual_control::of()
{
    task_handle_manual_control *task = pool.allocate();
    new (task) task_handle_manual_control;
    return *task;
}

void
task_handle_manual_control::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(20));
        uint16_t raw   = DS2_NONE;

        if (count &&
            device_dualshock2_read(DEVICE_DUALSHOCK2_1, &raw) == RESULT_OK)
        {
            uint16_t commands = mapper_dualshock2_control_read(raw);
            pathbot_handle_commands(commands);
        }
    }
}

task_handle_manual_control::task_handle_manual_control()
    : task_base("task_manual", 2)
{
}

} // namespace app
