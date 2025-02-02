#include <core.h>

int
main(void)
{
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_port_motion_init();
    core_port_remote_control_init();

    while (1)
    {
        core_task_remote_control_receive(&vehicle);
        core_task_motion_update(&vehicle);
    }
}