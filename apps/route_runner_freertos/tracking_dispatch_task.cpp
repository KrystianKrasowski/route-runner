#include "tracking_dispatch_task.hpp"
#include "mapper/qtrhd06a_coordinates.hpp"

namespace app
{

tracking_dispatch_task&
tracking_dispatch_task::of(
    const device::qtrhd06a& qtrhd06a,
    const event_group&      event_group,
    linebot::api&           api
)
{
    static tracking_dispatch_task task{qtrhd06a, event_group, api};
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

            event_group_.set_bits(actions.as_uint());
        }
    }
}

} // namespace app
