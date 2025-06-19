#include "task.h"
#include <adapters/coords_qtrhd06a.h>
#include <adapters/dump_serial.h>
#include <adapters/route_guard.h>
#include <devices/dualshock2.h>
#include <devices/qtrhd06a.h>
#include <mappers/dualshock2_control.h>
#include <mappers/qtrhd06a_coords.h>
#include <pathbot/api.h>
#include <utils/result.h>

void
task_handle_manual_control(void)
{
    uint16_t raw = DS2_NONE;

    if (device_dualshock2_read(DEVICE_DUALSHOCK2_1, &raw) == RESULT_OK)
    {
        uint16_t commands = mapper_dualshock2_control_read(raw);
        pathbot_handle_commands(commands);
    }
}

void
task_handle_route_tracking(void)
{
    uint8_t const coords_size = DEVICE_QTRHD06A_VALUES_LENGTH;
    uint8_t       raw_values[coords_size];

    if (device_qtrhd06a_read(DEVICE_QTRHD06A_1, raw_values) == RESULT_OK)
    {
        // TODO: Some factory here
        pathbot_coords_t coords = {
            .coords  = {0, 0, 0, 0, 0, 0},
            .length  = PATHBOT_MAX_COORDS_LENGTH,
            .weights = PATHBOT_COORDS6_WEIGHTS,
        };

        mapper_qtrhd06a_coords_read(raw_values, coords_size, &coords);
        pathbot_handle_coords(&coords);
    }
}

void
task_handle_immediate_stop(void)
{
    if (adapter_route_guard_read() == RESULT_TIMEOUT)
    {
        pathbot_handle_route_guard_timeout();
    }
}

void
task_handle_domain_dump(void)
{
    if (adapter_domain_dump_request_read() == RESULT_OK)
    {
        pathbot_handle_store_dump();
    }
}
