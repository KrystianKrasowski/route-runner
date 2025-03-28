#include <core/ports.h>
#include <core/vehicle.h>
#include <stdio.h>
#include <usart2.h>

void
core_port_debug_init(void)
{
    usart2_tx_init();
}

void
core_port_debug_apply(core_vehicle_t *vehicle)
{
    core_coords_t coords = core_vehicle_get_coords(vehicle);

    uint8_t left_3  = core_coords_get_place(&coords, CORE_COORDS_PLACE_LEFT_3);
    uint8_t left_2  = core_coords_get_place(&coords, CORE_COORDS_PLACE_LEFT_2);
    uint8_t left_1  = core_coords_get_place(&coords, CORE_COORDS_PLACE_LEFT_1);
    uint8_t right_1 = core_coords_get_place(&coords, CORE_COORDS_PLACE_RIGHT_1);
    uint8_t right_2 = core_coords_get_place(&coords, CORE_COORDS_PLACE_RIGHT_2);
    uint8_t right_3 = core_coords_get_place(&coords, CORE_COORDS_PLACE_RIGHT_3);

    int8_t correction = core_vehicle_get_motion_correction(vehicle);

    printf("Coords. L3: %d, L2: %d, L1: %d, R1: %d, R2: %d, R3: %d, "
           "Correction: %d\n",
           left_3,
           left_2,
           left_1,
           right_1,
           right_2,
           right_3,
           correction);
}