#include "route_guard_toggle_task.hpp"

namespace app
{

route_guard_toggle_task&
route_guard_toggle_task::of(linebot::api& api, EventGroupHandle_t even_group)
{
    static route_guard_toggle_task task{api, even_group};
    return task;
}

void
route_guard_toggle_task::run()
{
    auto bits_to_wait = linebot::actions::ROUTE_GUARD_TOGGLE;

    while (1)
    {
        auto events = xEventGroupWaitBits(
            event_group_, bits_to_wait, pdTRUE, pdTRUE, pdMS_TO_TICKS(5)
        );

        if (events & bits_to_wait)
        {
            api_.toggle_route_guard();
        }
    }
}

} // namespace app
