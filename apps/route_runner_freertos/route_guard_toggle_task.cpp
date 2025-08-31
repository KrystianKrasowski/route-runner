#include "route_guard_toggle_task.hpp"

namespace app
{

route_guard_toggle_task&
route_guard_toggle_task::of(const event_group& event_group, linebot::api& api)
{
    static route_guard_toggle_task task{event_group, api};
    return task;
}

void
route_guard_toggle_task::run()
{
    auto bits_to_wait = linebot::actions::ROUTE_GUARD_TOGGLE;

    while (1)
    {
        auto events = event_group_.wait_bits(bits_to_wait, true, true, 5);

        if (events & bits_to_wait)
        {
            api_.toggle_route_guard();
        }
    }
}

} // namespace app
