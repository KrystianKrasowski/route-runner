#ifndef _APPLICATION_TASK_IMMEDIATE_STOP_H
#define _APPLICATION_TASK_IMMEDIATE_STOP_H

#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class immediate_stop_task : public task_base<immediate_stop_task, 48>
{
public:

    static immediate_stop_task&
    of(linebot::api& api);

    immediate_stop_task(immediate_stop_task& other) = delete;

    immediate_stop_task&
    operator=(immediate_stop_task& other) = delete;

    void
    run();

private:

    linebot::api api_;

    explicit immediate_stop_task(linebot::api& api)
        : task_base{"route guard", 3},
          api_{api}
    {
    }
};

} // namespace app

#endif
