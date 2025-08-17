#include "manual_pid_tune_task.hpp"

namespace app
{

manual_pid_tune_task&
manual_pid_tune_task::of(const event_group& event_group, linebot::api& api)
{
    static manual_pid_tune_task task{event_group, api};
    return task;
}

void
manual_pid_tune_task::run()
{
    auto bits_to_wait = linebot::actions::TUNE_PID;

    while (1)
    {
        auto events = event_group_.wait_bits(bits_to_wait, true, true, 20);

        if (events & bits_to_wait)
        {
            api_.tune_pid_regulator();
        }
    }
}

} // namespace app
