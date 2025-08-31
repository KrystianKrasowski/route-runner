#pragma once

#include "FreeRTOS.h"
#include "device/tree.hpp"
#include "domain_dump_task.hpp"
#include "event_group.hpp"
#include "event_groups.h"
#include "immediate_stop_task.hpp"
#include "isr_event_emitter_adapter.hpp"
#include "linebot/api.hpp"
#include "linebot/data_store.hpp"
#include "linebot/motion_port.hpp"
#include "linebot/route_guard_port.hpp"
#include "linebot/status_indicator_port.hpp"
#include "manual_dispatch_task.hpp"
#include "manual_mode_switch_task.hpp"
#include "manual_motion_task.hpp"
#include "manual_pid_tune_task.hpp"
#include "memory_usage_dump_task.hpp"
#include "mutex.hpp"
#include "route_guard_toggle_task.hpp"
#include "shell_command_task.hpp"
#include "shell_output_task.hpp"
#include "stream_buffer.h"
#include "stream_buffer.hpp"
#include "tracking_dispatch_task.hpp"
#include "tracking_mode_switch_task.hpp"
#include "tracking_motion_task.hpp"

namespace app
{

class task_factory
{
public:

    task_factory(device::tree& devices, isr_event_emitter_adapter& events);

    manual_dispatch_task&
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

    immediate_stop_task&
    create_immediate_stop_task();

    shell_command_task&
    create_shell_command_task();

    domain_dump_task&
    create_domain_dump_task();

    shell_output_task&
    create_shell_output_task();

    memory_usage_dump_task&
    create_memory_usage_dump_task();

private:

    // Look out for this class growth. If there was more event groups, mutexes,
    // etc, consider extracting them to separate modules, other factories maybe

    device::tree&              devices_;
    isr_event_emitter_adapter& events_;

    linebot::data_store*            store_               = nullptr;
    linebot::motion_port*           motion_              = nullptr;
    linebot::status_indicator_port* status_indicator_    = nullptr;
    linebot::route_guard_port*      route_guard_         = nullptr;
    linebot::api*                   api_                 = nullptr;
    event_group*                    shell_event_group_   = nullptr;
    event_group*                    linebot_event_group_ = nullptr;
    shell_stream*                   shell_stream_        = nullptr;
    mutex*                          shell_mutex_         = nullptr;

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

    inline event_group&
    get_or_create_shell_event_group();

    inline event_group&
    get_or_create_linebot_event_group();

    inline shell_stream&
    get_or_create_shell_stream();

    inline mutex&
    get_or_create_shell_mutex();
};

} // namespace app
