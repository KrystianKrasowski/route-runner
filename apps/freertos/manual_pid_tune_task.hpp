#include "FreeRTOS.h"
#include "event_group.hpp"
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
    of(const event_group& event_group, linebot::api& api);

    void
    run();

    manual_pid_tune_task(const manual_pid_tune_task& other) = delete;

    manual_pid_tune_task(manual_pid_tune_task&& other) = delete;

    manual_pid_tune_task&
    operator=(const manual_pid_tune_task& other) = delete;

    manual_pid_tune_task&
    operator=(manual_pid_tune_task&& other) = delete;

private:

    const event_group& event_group_;
    linebot::api&      api_;

    manual_pid_tune_task(const event_group& event_group, linebot::api& api)
        : task_base{"mnpid", 1},
          event_group_{event_group},
          api_{api}
    {
    }
};

} // namespace app
