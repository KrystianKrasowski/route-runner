#include "manual_pid_tune_task.hpp"

namespace app
{

manual_pid_tune_task&
manual_pid_tune_task::of(linebot::api& api, EventGroupHandle_t event_group)
{
    static manual_pid_tune_task task{api, event_group};
    return task;
}

void
manual_pid_tune_task::run()
{
    auto bits_to_wait = linebot::actions::TUNE_PID;

    while (1)
    {
        auto events = xEventGroupWaitBits(
            event_group_, bits_to_wait, pdTRUE, pdTRUE, pdMS_TO_TICKS(20)
        );

        if (events & bits_to_wait)
        {
            api_.tune_pid_regulator();
        }
    }
}

} // namespace app
