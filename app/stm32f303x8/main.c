#include <core/ports.h>
#include <core/vehicle.h>
#include <sysclock.h>
#include <tasks.h>

int
main(void)
{
    sysclock_init();

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    core_port_motion_init();
    core_port_remote_control_init();
    core_port_state_indicator_init();
    core_port_line_position_init();

    while (1)
    {
        tasks_run(&vehicle);
    }
}