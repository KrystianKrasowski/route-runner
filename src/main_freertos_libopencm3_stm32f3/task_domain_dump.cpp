#include "devices/serial.h"
#include "pathbot/api.h"
#include "task_base.hpp"
#include "task_domain_dump.hpp"
#include "utils/result.h"
#include <cstdint>
#include <etl/pool.h>

namespace app
{

static etl::pool<task_domain_dump, 1> pool;

task_domain_dump&
task_domain_dump::of()
{
    task_domain_dump *task = pool.allocate();
    new (task) task_domain_dump;
    return *task;
}

void
task_domain_dump::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000));

        if (count && device_serial_read(DEVICE_SERIAL_1, 'd') == RESULT_OK)
        {
            pathbot_handle_store_dump();
        }
    }
}

task_domain_dump::task_domain_dump() : task_base("domain dump", 1)
{
}

} // namespace app
