#include "l293.h"
#include "sysclock.h"
#include <drivers/devices.h>

void
devices_init(void)
{
    sysclock_init();
    l293_init();
}