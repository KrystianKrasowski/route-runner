#include <core.h>
#include <stdio.h>
#include <usart2.h>

void
core_port_motion_init(void)
{
    usart2_tx_init();
}

void
core_port_motion_apply(core_motion_t *motion)
{
    printf("Direction: %d, angle: %d\n", motion->direction, motion->angle);
}