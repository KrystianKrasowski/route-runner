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
    device::g_device_tree.init(events);

    app::task_factory task_factory{device::g_device_tree, events};

#ifdef __DEBUG
    auto& manual_dispatch = task_factory.create_manual_control_dispatch_task();
    auto& manual_motion   = task_factory.create_manual_motion_task();
    auto& manual_mode     = task_factory.create_manual_mode_switch_task();
    auto& manual_pid_tune = task_factory.create_manual_pid_tune_task();
    auto& tracking_dispatch = task_factory.create_tracking_dispatch_task();
    auto& tracking_motion   = task_factory.create_tracking_motion_task();
    auto& tracking_mode     = task_factory.create_tracking_mode_switch_task();
    auto& route_guard       = task_factory.create_route_guard_toggle_task();
    auto& immediate_stop    = task_factory.create_immediate_stop_task();
    auto& shell_command     = task_factory.create_shell_command_task();
    auto& domain_dump       = task_factory.create_domain_dump_task();
    auto& shell_output      = task_factory.create_shell_output_task();
    auto& memory_usage      = task_factory.create_memory_usage_dump_task();

    memory_usage.monitor(manual_dispatch.describe());
    memory_usage.monitor(manual_motion.describe());
    memory_usage.monitor(manual_mode.describe());
    memory_usage.monitor(manual_pid_tune.describe());
    memory_usage.monitor(tracking_dispatch.describe());
    memory_usage.monitor(tracking_motion.describe());
    memory_usage.monitor(tracking_mode.describe());
    memory_usage.monitor(route_guard.describe());
    memory_usage.monitor(immediate_stop.describe());
    memory_usage.monitor(shell_command.describe());
    memory_usage.monitor(domain_dump.describe());
    memory_usage.monitor(shell_output.describe());
    memory_usage.monitor(memory_usage.describe());
#else
    (void)task_factory.create_manual_control_dispatch_task();
    (void)task_factory.create_manual_motion_task();
    (void)task_factory.create_manual_mode_switch_task();
    (void)task_factory.create_manual_pid_tune_task();
    (void)task_factory.create_tracking_dispatch_task();
    (void)task_factory.create_tracking_motion_task();
    (void)task_factory.create_tracking_mode_switch_task();
    (void)task_factory.create_route_guard_toggle_task();
    (void)task_factory.create_immediate_stop_task();
#endif

    (void)app::stack_overflow_handler::hook(
        device::g_device_tree.blink_,
        device::g_device_tree.motor_left_,
        device::g_device_tree.motor_right_
    );

    vTaskStartScheduler();

    // trap here in case of the scheduler error
    while (1)
    {
    }
}
