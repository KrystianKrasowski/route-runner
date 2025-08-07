#include "manual_mode_switch_task.hpp"

namespace app
{

manual_mode_switch_task&
manual_mode_switch_task::of(linebot::api& api, EventGroupHandle_t event_group)
{
    static manual_mode_switch_task task{api, event_group};
    return task;
}

void
manual_mode_switch_task::run()
{
    auto bits_to_wait = linebot::actions::CHANGE_MODE;

    while (1)
    {
        auto events = xEventGroupWaitBits(
            event_group_, bits_to_wait, pdTRUE, pdTRUE, pdMS_TO_TICKS(20)
        );

        if (events & bits_to_wait)
        {
            api_.switch_mode_by_remote();
        }
    }
}

} // namespace app
