#include <core/vehicle.h>
#include <sysclock.h>
#include <tasks.h>

int
main(void)
{
    sysclock_init();
    tasks_init();

    core_vehicle_t vehicle;
    core_vehicle_init(&vehicle);

    while (1)
    {
        tasks_run(&vehicle);
    }
}