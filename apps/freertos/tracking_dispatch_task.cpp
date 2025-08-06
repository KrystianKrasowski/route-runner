#include "tracking_dispatch_task.hpp"
#include "mapper/qtrhd06a_coordinates.hpp"

namespace app
{

tracking_dispatch_task&
tracking_dispatch_task::of(
    device::qtrhd06a&  qtrhd06a,
    linebot::api&      api,
    EventGroupHandle_t event_group
)
{
    static tracking_dispatch_task task{qtrhd06a, api, event_group};
    return task;
}

void
tracking_dispatch_task::run()
{
    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(5));

        if (count)
        {
            auto raw_values = qtrhd06a_.read();
            auto actions    = api_.query(mapper::map(raw_values));

            xEventGroupSetBits(event_group_, actions.as_uint());
        }
    }
}

} // namespace app
