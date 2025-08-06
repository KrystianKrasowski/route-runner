#include "FreeRTOS.h"
#include "device/tree.hpp"
#include "isr_event_emitter_adapter.hpp"
#include "stack_overflow_handler.hpp"
#include "task.h"
#include "task_factory.hpp"

app::isr_event_emitter_adapter events;

int
main()
{
    auto devices = device::tree::of(events);

    app::task_factory task_factory{devices, events};

    // don't need the instances for these right now
    (void)task_factory.create_manual_control_dispatch_task();
    (void)task_factory.create_manual_motion_task();
    (void)task_factory.create_manual_mode_switch_task();
    (void)task_factory.create_manual_pid_tune_task();
    (void)task_factory.create_tracking_dispatch_task();
    (void)task_factory.create_tracking_motion_task();
    (void)task_factory.create_tracking_mode_switch_task();
    (void)task_factory.create_route_guard_toggle_task();
    (void)task_factory.create_immediate_stop_task();
    (void)task_factory.create_shell_command_task();
    (void)task_factory.create_domain_dump_task();

    (void)app::stack_overflow_handler::hook(devices.blink_);

    vTaskStartScheduler();

    // trap here in case of the scheduler error
    while (1)
    {
    }
}
