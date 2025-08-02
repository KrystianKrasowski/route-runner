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
#include "task_domain_dump.hpp"
#include "task_immediate_stop.hpp"
#include "task_manual_control.hpp"
#include "task_route_tracking.hpp"
#include "task_shell_command.hpp"

namespace app
{

class task_factory
{
public:

    task_factory(device::tree& devices, isr_event_emitter_adapter& events);

    task_manual_control&
    create_manual_control_task();

    task_route_tracking&
    create_route_tracking_task();

    task_immediate_stop&
    create_immediate_stop_task();

    task_shell_command&
    create_shell_command_task();

    task_domain_dump&
    create_domain_dump_task();

private:

    static StaticEventGroup_t shell_event_group_buffer_;

    device::tree&              devices_;
    isr_event_emitter_adapter& events_;

    linebot::data_store*            store_;
    linebot::motion_port*           motion_            = nullptr;
    linebot::status_indicator_port* status_indicator_  = nullptr;
    linebot::route_guard_port*      route_guard_       = nullptr;
    linebot::printer_port*          printer_           = nullptr;
    linebot::api*                   api_               = nullptr;
    EventGroupHandle_t              shell_event_group_ = nullptr;

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
};

} // namespace app
