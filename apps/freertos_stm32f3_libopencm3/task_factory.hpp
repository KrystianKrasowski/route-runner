#pragma once

#include "adapter/motion_l293.hpp"
#include "adapter/printer_shell.hpp"
#include "adapter/route_guard_timeout.hpp"
#include "adapter/status_indicator_toggle_sequence.hpp"
#include "device/tree.hpp"
#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "linebot/motion_port.hpp"
#include "linebot/printer_port.hpp"
#include "linebot/route_guard_port.hpp"
#include "linebot/status_indicator_port.hpp"
#include "task_immediate_stop.hpp"
#include "task_manual_control.hpp"
#include "task_route_tracking.hpp"
#include "task_shell_command_dispatch.hpp"

namespace app
{

class task_factory
{
public:

    task_factory(device::tree& devices, linebot::data_store& store)
        : devices_{devices},
          store_{store}
    {
    }

    task_manual_control&
    create_manual_control_task()
    {
        auto& api  = get_or_create_api();
        auto& task = task_manual_control::of(devices_.remote_control_, api);
        task.register_rtos_task();
        return task;
    }

    task_route_tracking&
    create_route_tracking_task()
    {
        auto& api  = get_or_create_api();
        auto& task = task_route_tracking::of(devices_.line_sensor_, api);
        task.register_rtos_task();
        return task;
    }

    task_immediate_stop&
    create_immediate_stop_task()
    {
        auto& api  = get_or_create_api();
        auto& task = task_immediate_stop::of(api);
        task.register_rtos_task();
        return task;
    }

    task_shell_command_dispatch&
    create_shell_command_dispatch_task()
    {
        auto& api  = get_or_create_api();
        auto& task = task_shell_command_dispatch::of(devices_.shell_, api);
        task.register_rtos_task();
        return task;
    }

private:

    device::tree&                   devices_;
    linebot::data_store&            store_;
    linebot::motion_port*           motion_           = nullptr;
    linebot::status_indicator_port* status_indicator_ = nullptr;
    linebot::route_guard_port*      route_guard_      = nullptr;
    linebot::printer_port*          printer_          = nullptr;
    linebot::api*                   api_              = nullptr;

    linebot::api&
    get_or_create_api()
    {
        if (!api_)
        {
            auto& motion           = get_or_create_motion();
            auto& status_indicator = get_or_create_status_indicator();
            auto& route_guard      = get_or_create_route_guard();
            auto& printer          = get_or_create_printer();

            api_ = &linebot::api::of(
                store_, motion, status_indicator, route_guard, printer
            );
        }

        return *api_;
    }

    linebot::motion_port&
    get_or_create_motion()
    {
        if (!motion_)
        {
            motion_ = &adapter::motion_l293::of(
                devices_.motor_left_, devices_.motor_right_
            );
        }

        return *motion_;
    }

    linebot::status_indicator_port&
    get_or_create_status_indicator()
    {
        if (!status_indicator_)
        {
            status_indicator_ =
                &adapter::status_indicator_toggle_sequence::of(devices_.blink_);
        }

        return *status_indicator_;
    }

    linebot::route_guard_port&
    get_or_create_route_guard()
    {
        if (!route_guard_)
        {
            route_guard_ =
                &adapter::route_guard_timeout::of(devices_.offroute_timeout_);
        }

        return *route_guard_;
    }

    linebot::printer_port&
    get_or_create_printer()
    {
        if (!printer_)
        {
            printer_ = &adapter::printer_shell::of(devices_.shell_);
        }

        return *printer_;
    }
};

} // namespace app
