#include "task.h"
#include <adapters.h>
#include <linebot/api.h>
#include <sysclock.h>

int
main(void)
{
    sysclock_init();

    adapters_mode_init();
    adapters_coords_init();
    adapters_control_init();
    adapters_motion_init();

    linebot_init();

    linebot_t linebot;
    linebot_acquire_default(&linebot);

    while (1)
    {
        task_handle_manual_control(linebot);
        task_handle_route_tracking(linebot);
        task_handle_immediate_stop(linebot);
    }
}