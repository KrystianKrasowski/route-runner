#include "tracking_mode_switch_task.hpp"

namespace app
{

tracking_mode_switch_task&
tracking_mode_switch_task::of(linebot::api& api, EventGroupHandle_t event_group)
{
    static tracking_mode_switch_task task{api, event_group};
    return task;
}

void
tracking_mode_switch_task::run()
{
    auto bits_to_wait = linebot::actions::CHANGE_MODE_BY_COORDS;

    while (1)
    {
        auto events = xEventGroupWaitBits(
            event_group_, bits_to_wait, pdTRUE, pdTRUE, pdMS_TO_TICKS(5)
        );

        if (events & bits_to_wait)
        {
            api_.switch_mode_by_line_position();
        }
    }
}

} // namespace app
