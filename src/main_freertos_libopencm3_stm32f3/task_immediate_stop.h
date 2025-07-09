#ifndef _APPLICATION_TASK_IMMEDIATE_STOP_H
#define _APPLICATION_TASK_IMMEDIATE_STOP_H

#include "task_base.h"

namespace app
{

class task_immediate_stop : public task_base<task_immediate_stop, 48>
{
public:

    static task_immediate_stop&
    of();

    task_immediate_stop(task_immediate_stop& other) = delete;

    task_immediate_stop&
    operator=(task_immediate_stop& other) = delete;

    void
    run();

private:

    task_immediate_stop();
};

} // namespace app

#endif
