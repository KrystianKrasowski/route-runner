#include "task_manual_motion.hpp"

namespace app
{

task_manual_motion&
task_manual_motion::of(linebot::api& api, EventGroupHandle_t event_group)
{
    static task_manual_motion task = task_manual_motion{api, event_group};
    return task;
}

void
task_manual_motion::run()
{
    
}

} // namespace app
