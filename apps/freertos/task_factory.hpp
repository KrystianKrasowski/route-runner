#pragma once

#include "FreeRTOS.h"
#include "device/tree.hpp"
#include "event_groups.h"
#include "isr_event_emitter_adapter.hpp"
#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "linebot/motion_port.hpp"
#include "linebot/printer_port.hpp"
#include "linebot/route_guard_port.hpp"
#include "linebot/status_indicator_port.hpp"
#include "manual_control_dispatch_task.hpp"
#include "manual_mode_switch_task.hpp"
#include "manual_motion_task.hpp"
#include "manual_pid_tune_task.hpp"
#include "route_guard_toggle_task.hpp"
#include "task_domain_dump.hpp"
#include "task_immediate_stop.hpp"
#include "task_shell_command.hpp"
#include "tracking_dispatch_task.hpp"
#include "tracking_mode_switch_task.hpp"
#include "tracking_motion_task.hpp"

namespace app
{

class task_factory
{
public:

    task_factory(device::tree& devices, isr_event_emitter_adapter& events);

    manual_control_dispatch_task&
    create_manual_control_dispatch_task();

    manual_motion_task&
    create_manual_motion_task();

    manual_mode_switch_task&
    create_manual_mode_switch_task();

    manual_pid_tune_task&
    create_manual_pid_tune_task();

    tracking_dispatch_task&
    create_tracking_dispatch_task();

    tracking_motion_task&
    create_tracking_motion_task();

    tracking_mode_switch_task&
    create_tracking_mode_switch_task();

    route_guard_toggle_task&
    create_route_guard_toggle_task();

    task_immediate_stop&
    create_immediate_stop_task();

    task_shell_command&
    create_shell_command_task();

    task_domain_dump&
    create_domain_dump_task();

private:

    // Look out for this class growth. If there was more event groups, mutexes,
    // etc, consider extracting them to separate modules, other factories maybe
    static StaticEventGroup_t shell_event_group_buffer_;
    static StaticEventGroup_t linebot_event_group_buffer_;

    device::tree&              devices_;
    isr_event_emitter_adapter& events_;

    linebot::data_store*            store_               = nullptr;
    linebot::motion_port*           motion_              = nullptr;
    linebot::status_indicator_port* status_indicator_    = nullptr;
    linebot::route_guard_port*      route_guard_         = nullptr;
    linebot::printer_port*          printer_             = nullptr;
    linebot::api*                   api_                 = nullptr;
    EventGroupHandle_t              shell_event_group_   = nullptr;
    EventGroupHandle_t              linebot_event_group_ = nullptr;

    linebot::api&
    get_or_create_api();

    linebot::data_store&
    get_or_create_store();

    inline linebot::motion_port&
    get_or_create_motion();

    inline linebot::status_indicator_port&
    get_or_create_status_indicator();

    inline linebot::route_guard_port&
    get_or_create_route_guard();

    inline linebot::printer_port&
    get_or_create_printer();

    inline EventGroupHandle_t
    get_or_create_shell_event_group();

    EventGroupHandle_t
    get_or_create_linebot_event_group();
};

} // namespace app
