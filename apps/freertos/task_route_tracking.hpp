#ifndef _APPLICATION_TASK_ROUTE_TRACKING_H
#define _APPLICATION_TASK_ROUTE_TRACKING_H

#include "device/qtrhd06a.hpp"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class task_route_tracking : public task_base<task_route_tracking, 96>
{
public:

    static task_route_tracking&
    of(device::qtrhd06a& line_sensor, linebot::api& api);

    task_route_tracking(task_route_tracking& other) = delete;

    task_route_tracking&
    operator=(task_route_tracking& other) = delete;

    void
    run();

private:

    device::qtrhd06a& line_sensor_;
    linebot::api&     api_;

    task_route_tracking(device::qtrhd06a& line_sensor, linebot::api& api)
        : task_base{"tracking", 2},
          line_sensor_{line_sensor},
          api_{api}
    {
    }
};

} // namespace app

#endif
