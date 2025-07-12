#include "FreeRTOS.h"
#include "devices/qtrhd06a.h"
#include "mappers/qtrhd06a_coords.h"
#include "pathbot/api.h"
#include "pathbot/domain.h"
#include "task_base.hpp"
#include "task_route_tracking.hpp"
#include "utils/result.h"
#include <cstdint>
#include <etl/pool.h>

namespace app
{

static etl::pool<task_route_tracking, 1> pool;

task_route_tracking&
task_route_tracking::of()
{
    task_route_tracking *task = pool.allocate();
    new (task) task_route_tracking;
    return *task;
}

void
task_route_tracking::run()
{
    while (1)
    {
        uint32_t      count       = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(5));
        uint8_t const coords_size = DEVICE_QTRHD06A_VALUES_LENGTH;
        uint8_t       raw[coords_size];

        if (count && device_qtrhd06a_read(DEVICE_QTRHD06A_1, raw) == RESULT_OK)
        {
            // TODO: some factory here
            pathbot_coords_t coords = {
                .coords  = {0, 0, 0, 0, 0, 0},
                .weights = {-100, -40, -20, 20, 40, 100},
                .length  = PATHBOT_MAX_COORDS_LENGTH,
            };

            mapper_qtrhd06a_coords_read(raw, coords_size, &coords);
            pathbot_handle_coords(&coords);
        }
    }
}

task_route_tracking::task_route_tracking() : task_base("tracking", 3)
{
}

} // namespace app
