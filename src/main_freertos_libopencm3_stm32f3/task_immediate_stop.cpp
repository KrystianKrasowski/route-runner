#include "FreeRTOS.h"
#include "pathbot/api.h"
#include "task_base.h"
#include "task_immediate_stop.h"
#include <cstdint>
#include <etl/pool.h>

namespace app
{

static etl::pool<task_immediate_stop, 1> pool;

task_immediate_stop&
task_immediate_stop::of()
{
    task_immediate_stop *task = pool.allocate();
    new (task) task_immediate_stop;
    return *task;
}

void
task_immediate_stop::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000));

        if (count)
        {
            pathbot_handle_route_guard_timeout();
        }
    }
}

task_immediate_stop::task_immediate_stop() : task_base("route guard", 3)
{
}

} // namespace app
