#include "FreeRTOS.h"
#include "devices/blink.h"
#include "notifications.h"
#include "task.h"
#include <devices/devices.h>
#include <devices/dualshock2.h>
#include <devices/qtrhd06a.h>
#include <devices/serial.h>
#include <mappers/dualshock2_control.h>
#include <mappers/qtrhd06a_coords.h>
#include <pathbot/api.h>
#include <pathbot/store.h>
#include <stddef.h>
#include <stdint.h>
#include <utils/result.h>

TaskHandle_t h_task_manual_control;
TaskHandle_t h_task_route_tracking;
TaskHandle_t h_task_immediate_stop;
TaskHandle_t h_task_domain_dump;

void
task_manual_control(void *p_parameters)
{
    (void)p_parameters;

    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(20));

        if (count == 0)
        {
            continue;
        }

        uint16_t raw = DS2_NONE;

        if (device_dualshock2_read(DEVICE_DUALSHOCK2_1, &raw) != RESULT_OK)
        {
            continue;
        }

        uint16_t commands = mapper_dualshock2_control_read(raw);
        pathbot_handle_commands(commands);
    }
}

void
task_route_tracking(void *p_parameters)
{
    (void)p_parameters;

    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(5));

        if (count == 0)
        {
            continue;
        }

        uint8_t const coords_size = DEVICE_QTRHD06A_VALUES_LENGTH;
        uint8_t       raw_coords[coords_size];

        if (device_qtrhd06a_read(DEVICE_QTRHD06A_1, raw_coords) != RESULT_OK)
        {
            continue;
        }

        // TODO: Some factory here
        pathbot_coords_t coords = {
            .coords  = {0, 0, 0, 0, 0, 0},
            .length  = PATHBOT_MAX_COORDS_LENGTH,
            .weights = PATHBOT_COORDS6_WEIGHTS,
        };

        mapper_qtrhd06a_coords_read(raw_coords, coords_size, &coords);
        pathbot_handle_coords(&coords);
    }
}

void
task_immediate_stop(void *p_parameters)
{
    (void)p_parameters;

    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000));

        if (count == 0)
        {
            continue;
        }

        pathbot_handle_route_guard_timeout();
    }
}

void
task_domain_dump(void *p_parameters)
{
    (void)p_parameters;

    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000));

        if (count == 0)
        {
            continue;
        }

        if (device_serial_read(DEVICE_SERIAL_1, 'd') != RESULT_OK)
        {
            continue;
        }

        pathbot_handle_store_dump();
    }
}

void
vApplicationStackOverflowHook(TaskHandle_t h_task, char *task_name)
{
    device_blink_set_toggles(DEVICE_BLINK_1, 6);

    while (1)
    {
        // trap
    }
}

int
main(void)
{
    devices_init();
    pathbot_store_init(NULL);
    notifications_init();

    (void)xTaskCreate(task_manual_control,
                      "task manual",
                      48,
                      NULL,
                      2,
                      &h_task_manual_control);

    (void)xTaskCreate(task_route_tracking,
                      "task tracking",
                      128,
                      NULL,
                      2,
                      &h_task_route_tracking);

    (void)xTaskCreate(task_immediate_stop,
                      "task route guard",
                      48,
                      NULL,
                      3,
                      &h_task_immediate_stop);

    (void)xTaskCreate(task_domain_dump,
                      "task domain dump",
                      256,
                      NULL,
                      1,
                      &h_task_domain_dump);

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
