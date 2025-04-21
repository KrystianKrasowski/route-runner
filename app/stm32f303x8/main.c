#include "task.h"
#include <adapters.h>
#include <linebot/api.h>
#include <sysclock.h>

int
main(void)
{
    sysclock_init();

    linebot_init();

    // TODO: Adapters should not initialize device drivers. Those drivers should
    // be initialized in the devices layer that is to be yet implemented
    adapters_mode_init();
    adapters_coords_init();
    adapters_control_init();
    adapters_motion_init();

    linebot_coords_t h_coords;
    // TODO: Handle error
    (void)adapters_coords_create_default(&h_coords);

    linebot_t h_linebot;
    // TODO: Handle error
    (void)linebot_acquire(LINEBOT_MODE_MANUAL, h_coords, 20, &h_linebot);

    while (1)
    {
        task_handle_manual_control(h_linebot);
        task_handle_route_tracking(h_linebot);
        task_handle_immediate_stop(h_linebot);
    }
}