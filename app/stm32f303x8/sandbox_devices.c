#include <devices/devices.h>
#include <devices/l293.h>

int
main(void)
{
    devices_init();

    devices_l293_set_right(DEVICES_L293_CHANNEL_12);
    devices_l293_set_left(DEVICES_L293_CHANNEL_34);
    devices_l293_disable(DEVICES_L293_CHANNEL_12);
    devices_l293_disable(DEVICES_L293_CHANNEL_34);

    while (1)
    {
    }

    return 0;
}