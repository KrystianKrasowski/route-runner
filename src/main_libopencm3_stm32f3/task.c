#include "task.h"
#include <adapters/control_dualshock2.h>
#include <adapters/coords_qtrhd06a.h>
#include <adapters/route_guard.h>
#include <devices/dualshock2.h>
#include <devices/qtrhd06a.h>
#include <pathbot/api.h>
#include <utils/result.h>

void
task_handle_manual_control()
{
    uint16_t commands;

    if (adapter_control_dualshock2_read(DEVICE_DUALSHOCK2_1, &commands) ==
        RESULT_OK)
    {
        pathbot_handle_commands(commands);
    }
}

void
task_handle_route_tracking()
{
    // TODO: Some factory here
    pathbot_coords_t coords = {
        .coords  = {0, 0, 0, 0, 0, 0},
        .length  = PATHBOT_MAX_COORDS_LENGTH,
        .weights = PATHBOT_COORDS6_WEIGHTS,
    };

    if (adapter_coords_qtrhd06a_read(DEVICE_QTRHD06A_1, &coords) == RESULT_OK)
    {
        pathbot_handle_coords(&coords);
    }
}

void
task_handle_immediate_stop()
{
    if (adapter_route_guard_read() == RESULT_TIMEOUT)
    {
        pathbot_handle_route_guard_timeout();
    }
}
