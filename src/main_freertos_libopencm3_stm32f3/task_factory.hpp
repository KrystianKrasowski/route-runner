#pragma once

#include "adapter/motion_l293.hpp"
#include "adapter/route_guard_timeout.hpp"
#include "adapter/status_indicator_toggle_sequence.hpp"
#include "device/tree.hpp"
#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "task_immediate_stop.hpp"
#include "task_manual_control.hpp"
#include "task_route_tracking.hpp"

namespace app
{

class task_factory
{
public:

    task_factory(device::tree& devices, linebot::data_store& store)
        : devices_{devices}
    {
        auto& motion =
            adapter::motion_l293::of(devices.motor_left_, devices.motor_right_);

        auto& status_indicator =
            adapter::status_indicator_toggle_sequence::of(devices.blink_);

        auto& route_guard =
            adapter::route_guard_timeout::of(devices.offroute_timeout_);

        api_ = &linebot::api::of(store, motion, status_indicator, route_guard);
    }

    task_manual_control&
    create_manual_control_task()
    {
        auto& task = task_manual_control::of(devices_.remote_control_, *api_);
        task.register_rtos_task();
        return task;
    }

    task_route_tracking&
    create_route_tracking_task()
    {
        auto& task = task_route_tracking::of(devices_.line_sensor_, *api_);
        task.register_rtos_task();
        return task;
    }

    task_immediate_stop&
    create_immediate_stop_task()
    {
        auto& task = task_immediate_stop::of(*api_);
        task.register_rtos_task();
        return task;
    }

private:

    device::tree& devices_;
    linebot::api* api_;
};

} // namespace app
