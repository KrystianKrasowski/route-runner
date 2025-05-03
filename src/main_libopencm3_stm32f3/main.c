#include "task.h"
#include <devices/devices.h>
#include <linebot/api.h>
#include <linebot/coords.h>
#include <stdint.h>

int
main(void)
{
    devices_init();
    linebot_init();

    linebot_coords_t h_coords;
    // TODO: Handle error
    (void)linebot_coords_acquire((uint8_t[]){0, 0, 0, 0, 0, 0}, 6, &h_coords);

    linebot_t h_linebot;
    // TODO: Handle error
    (void)linebot_acquire(LINEBOT_MODE_MANUAL, h_coords, 20, &h_linebot);

    while (1)
    {
        task_handle_manual_control(h_linebot);
        // task_handle_route_tracking(h_linebot);
        // task_handle_immediate_stop(h_linebot);
    }
}
