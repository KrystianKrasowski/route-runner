#include "FreeRTOS.h"
#include "task.h"
#include <devices/blink.h>
#include <devices/dualshock2.h>
#include <devices/l293.h>
#include <devices/qtrhd06a.h>
#include <devices/serial.h>
#include <mappers/dualshock2_control.h>
#include <mappers/qtrhd06a_coords.h>
#include <pathbot/api.h>
#include <stdint.h>
#include <utils/result.h>

void
app_handle_manual_control(void *p_params)
{
    (void)p_params;

    while (1)
    {

        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(20));
        uint16_t raw   = DS2_NONE;

        if (count &&
            device_dualshock2_read(DEVICE_DUALSHOCK2_1, &raw) == RESULT_OK)
        {
            uint16_t commands = mapper_dualshock2_control_read(raw);
            pathbot_handle_commands(commands);
        }
    }
}

void
app_handle_route_tracking(void *p_params)
{
    (void)p_params;

    while (1)
    {
        uint32_t      count       = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(5));
        uint8_t const coords_size = DEVICE_QTRHD06A_VALUES_LENGTH;
        uint8_t       raw[coords_size];

        if (count && device_qtrhd06a_read(DEVICE_QTRHD06A_1, raw) == RESULT_OK)
        {

            // TODO: Some factory here
            pathbot_coords_t coords = {
                .coords  = {0, 0, 0, 0, 0, 0},
                .length  = PATHBOT_MAX_COORDS_LENGTH,
                .weights = PATHBOT_COORDS6_WEIGHTS,
            };

            mapper_qtrhd06a_coords_read(raw, coords_size, &coords);
            pathbot_handle_coords(&coords);
        }
    }
}

void
app_handle_immediate_stop(void *p_params)
{
    (void)p_params;

    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000));

        if (count)
        {
            pathbot_handle_route_guard_timeout();
        }
    }
}

void
app_handle_domain_dump(void *p_params)
{
    (void)p_params;

    while (1)
    {
        uint32_t count = ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(1000));

        if (count && device_serial_read(DEVICE_SERIAL_1, 'd') == RESULT_OK)
        {
            pathbot_handle_store_dump();
        }
    }
}

void
vApplicationStackOverflowHook(TaskHandle_t h_task, char *task_name)
{
    (void)h_task;
    (void)task_name;

    device_blink_set_sequence(DEVICE_BLINK_1, 0xd);
    device_l293_rotate(DEVICE_L293_CHANNEL_12, DEVICE_L293_ROTATION_STOP);
    device_l293_rotate(DEVICE_L293_CHANNEL_34, DEVICE_L293_ROTATION_STOP);
    device_l293_disable(DEVICE_L293_CHANNEL_12);
    device_l293_disable(DEVICE_L293_CHANNEL_34);

    while (1)
    {
        // trap
    }
}
