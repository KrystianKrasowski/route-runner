#include <linebot.h>
#include <stdio.h>
#include <usart2.h>

void
linebot_port_motion_init(void)
{
    usart2_tx_init();
}

void
linebot_port_motion_apply(linebot_motion_t const motion)
{
    printf("Direction: %d, correction: %d\n",
           linebot_motion_get_direction(motion),
           linebot_motion_get_correction(motion));
}