#include "tracking_motion_task.hpp"

namespace app
{

tracking_motion_task&
tracking_motion_task::of(linebot::api& api, EventGroupHandle_t event_group)
{
    static tracking_motion_task task{api, event_group};
    return task;
}

void
tracking_motion_task::run()
{
    auto bits_to_wait = linebot::actions::APPLY_MANEUVER_BY_COORDS;

    while (1)
    {
        auto events = xEventGroupWaitBits(
            even_group_, bits_to_wait, pdTRUE, pdTRUE, pdMS_TO_TICKS(5)
        );

        if (events & bits_to_wait)
        {
            api_.apply_motion_by_line_position();
        }
    }
}

} // namespace app
