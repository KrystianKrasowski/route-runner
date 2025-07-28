#ifndef _APPLICATION_TASK_MANUAL_CONTROL_H
#define _APPLICATION_TASK_MANUAL_CONTROL_H

#include "device/dualshock2.hpp"
#include "linebot/api.hpp"
#include "task_base.hpp"

namespace app
{

class task_manual_control : public task_base<task_manual_control, 48>
{
public:

    static task_manual_control&
    of(device::dualshock2& dualshock2, linebot::api& api);

    task_manual_control(task_manual_control& other) = delete;

    task_manual_control&
    operator=(task_manual_control& other) = delete;

    void
    run();

private:

    device::dualshock2& dualshock2_;
    linebot::api&       api_;

    task_manual_control(device::dualshock2& dualshock2, linebot::api& api)
        : task_base{"manual", 2},
          dualshock2_{dualshock2},
          api_{api}
    {
    }
};

} // namespace app

#endif
