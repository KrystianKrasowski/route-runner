#include <dualshock2.h>
#include <stdio.h>
#include <sysclock.h>
#include <usart2.h>

int
main(void)
{
    sysclock_init();
    usart2_tx_init();
    dualshock2_init();

    while (1)
    {
    }

    return 0;
}