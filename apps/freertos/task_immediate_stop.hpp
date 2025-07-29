#ifndef _APPLICATION_TASK_IMMEDIATE_STOP_H
#define _APPLICATION_TASK_IMMEDIATE_STOP_H

#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class task_immediate_stop : public task_base<task_immediate_stop, 48>
{
public:

    static task_immediate_stop&
    of(linebot::api& api);

    task_immediate_stop(task_immediate_stop& other) = delete;

    task_immediate_stop&
    operator=(task_immediate_stop& other) = delete;

    void
    run();

private:

    linebot::api api_;

    explicit task_immediate_stop(linebot::api& api)
        : task_base{"route guard", 3},
          api_{api}
    {
    }
};

} // namespace app

#endif
