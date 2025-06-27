#include "FreeRTOS.h"
#include "application.h"
#include "notifications.h"
#include "task.h"
#include <devices/devices.h>
#include <pathbot/store.h>
#include <stddef.h>
#include <stdint.h>

#define STACK_DEPTH_TASK_MANUAL   48
#define STACK_DEPTH_TASK_TRACKING 128
#define STACK_DEPTH_TASK_DUMP     256

StaticTask_t task_manual_control_tcb;
StackType_t  task_manual_control_stack[STACK_DEPTH_TASK_MANUAL];
TaskHandle_t h_task_manual_control;

StaticTask_t task_route_tracking_tcb;
StackType_t  task_route_tracking_stack[STACK_DEPTH_TASK_TRACKING];
TaskHandle_t h_task_route_tracking;

StaticTask_t task_immediate_stop_tcb;
StackType_t  task_immediate_stop_stack[STACK_DEPTH_TASK_MANUAL];
TaskHandle_t h_task_immediate_stop;

StaticTask_t task_domain_dump_tcb;
StackType_t  task_domain_dump_stack[STACK_DEPTH_TASK_DUMP];
TaskHandle_t h_task_domain_dump;

int
main(void)
{
    devices_init();
    pathbot_store_init(NULL);
    notifications_init();

    h_task_manual_control = xTaskCreateStatic(app_handle_manual_control,
                                              "task manual",
                                              STACK_DEPTH_TASK_MANUAL,
                                              NULL,
                                              2,
                                              task_manual_control_stack,
                                              &task_manual_control_tcb);

    h_task_route_tracking = xTaskCreateStatic(app_handle_route_tracking,
                                              "task tracking",
                                              STACK_DEPTH_TASK_TRACKING,
                                              NULL,
                                              2,
                                              task_route_tracking_stack,
                                              &task_route_tracking_tcb);

    h_task_immediate_stop = xTaskCreateStatic(app_handle_immediate_stop,
                                              "task route guard",
                                              STACK_DEPTH_TASK_MANUAL,
                                              NULL,
                                              3,
                                              task_immediate_stop_stack,
                                              &task_immediate_stop_tcb);

    h_task_domain_dump = xTaskCreateStatic(app_handle_domain_dump,
                                           "task domain dump",
                                           STACK_DEPTH_TASK_DUMP,
                                           NULL,
                                           1,
                                           task_domain_dump_stack,
                                           &task_domain_dump_tcb);

    notifications_set_dualshock2_task(h_task_manual_control);
    notifications_set_route_convertions_task(h_task_route_tracking);
    notifications_set_route_guard_task(h_task_immediate_stop);
    notifications_set_serial_request_task(h_task_domain_dump);

    vTaskStartScheduler();

    while (1)
    {
        // should never reach here
    }
}
