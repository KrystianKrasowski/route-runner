#include "manual_motion_task.hpp"

namespace app
{

manual_motion_task&
manual_motion_task::of(
    linebot::api& api, EventGroupHandle_t event_group
)
{
    static manual_motion_task task{api, event_group};
    return task;
}

void
manual_motion_task::run()
{
    uint8_t bits_to_wait = linebot::actions::APPLY_MANEUVER;

    while (1)
    {
        auto events = xEventGroupWaitBits(
            event_group_, bits_to_wait, pdTRUE, pdTRUE, pdMS_TO_TICKS(20)
        );

        if (events & bits_to_wait)
        {
            api_.apply_motion_by_remote();
        }
    }
}

} // namespace app
