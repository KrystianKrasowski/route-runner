#ifndef _APPLICATION_TASK_ROUTE_TRACKING_H
#define _APPLICATION_TASK_ROUTE_TRACKING_H

#include "task_base.hpp"

namespace app
{

class task_route_tracking : public task_base<task_route_tracking, 80>
{
public:

    static task_route_tracking&
    of();

    task_route_tracking(task_route_tracking& other) = delete;

    task_route_tracking&
    operator=(task_route_tracking& other) = delete;

    void
    run();

private:

    task_route_tracking();
};

} // namespace app

#endif
