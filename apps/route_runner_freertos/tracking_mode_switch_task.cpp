#include "tracking_mode_switch_task.hpp"

namespace app
{

tracking_mode_switch_task&
tracking_mode_switch_task::of(const event_group& event_group, linebot::api& api)
{
    static tracking_mode_switch_task task{event_group, api};
    return task;
}

void
tracking_mode_switch_task::run()
{
    auto bits_to_wait = linebot::actions::CHANGE_MODE_BY_COORDS;

    while (1)
    {
        auto events = event_group_.wait_bits(bits_to_wait, true, true, 5);

        if (events & bits_to_wait)
        {
            api_.switch_mode_by_line_position();
        }
    }
}

} // namespace app
