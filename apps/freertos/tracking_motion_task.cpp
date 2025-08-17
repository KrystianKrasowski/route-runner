#include "tracking_motion_task.hpp"

namespace app
{

tracking_motion_task&
tracking_motion_task::of(const event_group& event_group, linebot::api& api)
{
    static tracking_motion_task task{event_group, api};
    return task;
}

void
tracking_motion_task::run()
{
    auto bits_to_wait = linebot::actions::APPLY_MANEUVER_BY_COORDS;

    while (1)
    {
        auto events = even_group_.wait_bits(bits_to_wait, true, true, 5);

        if (events & bits_to_wait)
        {
            api_.apply_motion_by_line_position();
        }
    }
}

} // namespace app
