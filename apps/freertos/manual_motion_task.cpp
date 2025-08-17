#include "manual_motion_task.hpp"

namespace app
{

manual_motion_task&
manual_motion_task::of(const event_group& event_group, linebot::api& api)
{
    static manual_motion_task task{event_group, api};
    return task;
}

void
manual_motion_task::run()
{
    uint8_t bits_to_wait = linebot::actions::APPLY_MANEUVER;

    while (1)
    {
        auto events = event_group_.wait_bits(bits_to_wait, true, true, 20);

        if (events & bits_to_wait)
        {
            api_.apply_motion_by_remote();
        }
    }
}

} // namespace app
