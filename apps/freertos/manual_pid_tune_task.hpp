#include "FreeRTOS.h"
#include "event_groups.h"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class manual_pid_tune_task
    : public task_base<manual_pid_tune_task, TASK_MEM_MANUAL_PID_TUNE>
{
public:

    static manual_pid_tune_task&
    of(linebot::api& api, EventGroupHandle_t event_group);

    void
    run();

    manual_pid_tune_task(manual_pid_tune_task& other) = delete;

    manual_pid_tune_task&
    operator=(manual_pid_tune_task& other) = delete;

    manual_pid_tune_task&&
    operator=(manual_pid_tune_task&& other) = delete;

private:

    linebot::api&      api_;
    EventGroupHandle_t event_group_;

    manual_pid_tune_task(linebot::api& api, EventGroupHandle_t event_group)
        : task_base{"mnpid", 1},
          api_{api},
          event_group_{event_group}
    {
    }
};

} // namespace app
