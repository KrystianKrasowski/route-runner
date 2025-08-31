#include "manual_mode_switch_task.hpp"

namespace app
{

manual_mode_switch_task&
manual_mode_switch_task::of(const event_group& event_group, linebot::api& api)
{
    static manual_mode_switch_task task{event_group, api};
    return task;
}

void
manual_mode_switch_task::run()
{
    auto bits_to_wait = linebot::actions::CHANGE_MODE;

    while (1)
    {
        auto events = event_group_.wait_bits(bits_to_wait, true, true, 20);

        if (events & bits_to_wait)
        {
            api_.switch_mode_by_remote();
        }
    }
}

} // namespace app
