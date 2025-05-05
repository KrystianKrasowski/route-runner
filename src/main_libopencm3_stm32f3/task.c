#include "task.h"
#include <adapters/control_dualshock2.h>
#include <adapters/coords_qtrhd06a.h>
#include <devices/dualshock2.h>
#include <devices/qtrhd06a.h>
#include <utils/result.h>

void
task_handle_manual_control(linebot_t const linebot)
{
    uint16_t commands;

    if (adapter_control_dualshock2_read(DEVICE_DUALSHOCK2_1, &commands) ==
        RESULT_OK)
    {
        // TODO: Handle failures
        (void)linebot_handle_manual_control(linebot, commands);
    }
}

void
task_handle_route_tracking(linebot_t const linebot)
{
    linebot_coords_t h_coords;

    if (adapter_coords_qtrhd06a_read(DEVICE_QTRHD06A_1, &h_coords) == RESULT_OK)
    {
        // TODO: Handle failures
        (void)linebot_handle_route_tracking(linebot, h_coords);
        (void)linebot_coords_release(h_coords);
    }
}

// void
// task_handle_immediate_stop(linebot_t const linebot)
// {
// if (adapters_is_route_guard_timeout())
// {
// // TODO: Handle failures
// (void)linebot_handle_immediate_stop(linebot);
// }
//}
