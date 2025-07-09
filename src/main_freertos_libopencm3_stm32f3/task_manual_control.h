#ifndef _APPLICATION_TASK_MANUAL_CONTROL_H
#define _APPLICATION_TASK_MANUAL_CONTROL_H

#include "task_base.h"

namespace app
{

class task_handle_manual_control
    : public task_base<task_handle_manual_control, 48>
{
public:

    static task_handle_manual_control&
    of();

    task_handle_manual_control(task_handle_manual_control& other) = delete;

    task_handle_manual_control&
    operator=(task_handle_manual_control& other) = delete;

    void
    run();

private:

    task_handle_manual_control();
};

} // namespace app

#endif
