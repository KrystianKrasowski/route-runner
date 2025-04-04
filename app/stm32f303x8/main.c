#include <core/vehicle.h>
#include <sysclock.h>
#include <tasks.h>

int
main(void)
{
    sysclock_init();
    tasks_init();

    core_mode_t     mode     = core_mode(CORE_MODE_MANUAL);
    core_coords_t   coords   = core_coords(0, 0, 0, 0, 0, 0);
    stack_t         errors   = stack(20);
    core_position_t position = core_position(coords, errors);
    core_vehicle_t  vehicle  = core_vehicle(mode, position);

    while (1)
    {
        tasks_run(&vehicle);
    }
}