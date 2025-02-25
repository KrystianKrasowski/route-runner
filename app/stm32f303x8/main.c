#include <core.h>
#include <sysclock.h>

int
main(void)
{
    sysclock_init();
    
    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);
    core_port_motion_init();
    core_port_remote_control_init();
    core_port_state_indicator_init();

    while (1)
    {
        core_task_remote_control_receive(&vehicle);
        core_task_motion_update(&vehicle);
        core_task_state_indicator_update(&vehicle);
    }
}