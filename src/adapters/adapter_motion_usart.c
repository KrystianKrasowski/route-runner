#include <core/vehicle.h>
#include <stdio.h>
#include <usart2.h>

void
core_port_motion_init(void)
{
    usart2_tx_init();
}

void
core_port_motion_apply(core_vehicle_t *vehicle)
{
    printf("Direction: %d, correction: %d\n",
           core_vehicle_get_motion_direction(vehicle),
           core_vehicle_get_motion_correction(vehicle));
}