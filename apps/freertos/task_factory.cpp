#include "task_factory.hpp"
#include "FreeRTOS.h"
#include "adapter/motion_l293.hpp"
#include "adapter/printer_shell.hpp"
#include "adapter/route_guard_timeout.hpp"
#include "adapter/status_indicator_toggle_sequence.hpp"
#include "device/isr_event_emitter.hpp"
#include "device/tree.hpp"
#include "event_groups.h"
#include "isr_event_emitter_adapter.hpp"
#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "linebot/motion_port.hpp"
#include "linebot/printer_port.hpp"
#include "linebot/route_guard_port.hpp"
#include "linebot/status_indicator_port.hpp"
#include "task_domain_dump.hpp"
#include "task_immediate_stop.hpp"
#include "task_shell_command.hpp"
#include "tracking_mode_switch_task.hpp"

namespace app
{

StaticEventGroup_t task_factory::shell_event_group_buffer_;
StaticEventGroup_t task_factory::linebot_event_group_buffer_;

task_factory::task_factory(
    device::tree& devices, isr_event_emitter_adapter& events
)
    : devices_{devices},
      events_{events}
{
}

manual_control_dispatch_task&
task_factory::create_manual_control_dispatch_task()
{
    auto  isr_event   = device::event_id::DUALSHOCK2_RX_COMPLETE;
    auto& api         = get_or_create_api();
    auto  event_group = get_or_create_linebot_event_group();
    auto& task        = manual_control_dispatch_task::of(
        devices_.remote_control_, api, event_group
    );

    task.register_rtos_task();
    events_.register_task_notification(isr_event, task.get_handle());

    return task;
}

manual_motion_task&
task_factory::create_manual_motion_task()
{
    auto& api         = get_or_create_api();
    auto  event_group = get_or_create_linebot_event_group();
    auto& task        = manual_motion_task::of(api, event_group);

    task.register_rtos_task();

    return task;
}

manual_mode_switch_task&
task_factory::create_manual_mode_switch_task()
{
    auto& api         = get_or_create_api();
    auto  event_group = get_or_create_linebot_event_group();
    auto& task        = manual_mode_switch_task::of(api, event_group);

    task.register_rtos_task();

    return task;
}

manual_pid_tune_task&
task_factory::create_manual_pid_tune_task()
{
    auto& api         = get_or_create_api();
    auto  event_group = get_or_create_linebot_event_group();
    auto& task        = manual_pid_tune_task::of(api, event_group);

    task.register_rtos_task();

    return task;
}

tracking_dispatch_task&
task_factory::create_tracking_dispatch_task()
{
    auto  isr_event   = device::event_id::QTRHD06A_CONVERSION_COMPLETE;
    auto& api         = get_or_create_api();
    auto  event_group = get_or_create_linebot_event_group();
    auto& task =
        tracking_dispatch_task::of(devices_.line_sensor_, api, event_group);

    task.register_rtos_task();
    events_.register_task_notification(isr_event, task.get_handle());

    return task;
}

tracking_motion_task&
task_factory::create_tracking_motion_task()
{
    auto& api         = get_or_create_api();
    auto  event_group = get_or_create_linebot_event_group();
    auto& task        = tracking_motion_task::of(api, event_group);

    task.register_rtos_task();

    return task;
}

tracking_mode_switch_task&
task_factory::create_tracking_mode_switch_task()
{
    auto& api         = get_or_create_api();
    auto  event_group = get_or_create_linebot_event_group();
    auto& task        = tracking_mode_switch_task::of(api, event_group);

    task.register_rtos_task();

    return task;
}

route_guard_toggle_task&
task_factory::create_route_guard_toggle_task()
{
    auto& api         = get_or_create_api();
    auto  event_group = get_or_create_linebot_event_group();
    auto& task        = route_guard_toggle_task::of(api, event_group);

    task.register_rtos_task();

    return task;
}

task_immediate_stop&
task_factory::create_immediate_stop_task()
{
    auto& api      = get_or_create_api();
    auto& task     = task_immediate_stop::of(api);
    auto  event_id = device::event_id::TIMEOUT;

    task.register_rtos_task();
    events_.register_task_notification(event_id, task.get_handle());

    return task;
}

task_shell_command&
task_factory::create_shell_command_task()
{
    auto& api         = get_or_create_api();
    auto  event_group = get_or_create_shell_event_group();
    auto& task     = task_shell_command::of(devices_.shell_, api, event_group);
    auto  event_id = device::event_id::SHELL_COMMANDED;

    task.register_rtos_task();
    events_.register_task_notification(event_id, task.get_handle());

    return task;
}

task_domain_dump&
task_factory::create_domain_dump_task()
{
    auto& api         = get_or_create_api();
    auto  event_group = get_or_create_shell_event_group();
    auto& task        = task_domain_dump::of(api, event_group);

    task.register_rtos_task();

    return task;
}

linebot::api&
task_factory::get_or_create_api()
{
    if (!api_)
    {
        auto& store            = get_or_create_store();
        auto& motion           = get_or_create_motion();
        auto& status_indicator = get_or_create_status_indicator();
        auto& route_guard      = get_or_create_route_guard();
        auto& printer          = get_or_create_printer();

        api_ = &linebot::api::of(
            store, motion, status_indicator, route_guard, printer
        );
    }

    return *api_;
}

linebot::data_store&
task_factory::get_or_create_store()
{
    if (!store_)
    {
        store_ = &linebot::data_store::of();
    }

    return *store_;
}

linebot::motion_port&
task_factory::get_or_create_motion()
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
task_factory::get_or_create_status_indicator()
{
    if (!status_indicator_)
    {
        status_indicator_ =
            &adapter::status_indicator_toggle_sequence::of(devices_.blink_);
    }

    return *status_indicator_;
}

linebot::route_guard_port&
task_factory::get_or_create_route_guard()
{
    if (!route_guard_)
    {
        route_guard_ =
            &adapter::route_guard_timeout::of(devices_.offroute_timeout_);
    }

    return *route_guard_;
}

linebot::printer_port&
task_factory::get_or_create_printer()
{
    if (!printer_)
    {
        printer_ = &adapter::printer_shell::of(devices_.shell_);
    }

    return *printer_;
}

EventGroupHandle_t
task_factory::get_or_create_shell_event_group()
{
    if (!shell_event_group_)
    {
        shell_event_group_ =
            xEventGroupCreateStatic(&shell_event_group_buffer_);
    }

    return shell_event_group_;
}

EventGroupHandle_t
task_factory::get_or_create_linebot_event_group()
{
    if (!linebot_event_group_)
    {
        linebot_event_group_ =
            xEventGroupCreateStatic(&linebot_event_group_buffer_);
    }

    return linebot_event_group_;
}

} // namespace app
