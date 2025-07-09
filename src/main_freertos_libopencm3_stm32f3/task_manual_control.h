#ifndef _APPLICATION_TASK_MANUAL_CONTROL_H
#define _APPLICATION_TASK_MANUAL_CONTROL_H

#include "task_base.h"

namespace app
{

class task_manual_control : public task_base<task_manual_control, 48>
{
public:

    static task_manual_control&
    of();

    task_manual_control(task_manual_control& other) = delete;

    task_manual_control&
    operator=(task_manual_control& other) = delete;

    void
    run();

private:

    task_manual_control();
};

} // namespace app

#endif
