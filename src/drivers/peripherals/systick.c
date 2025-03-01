#include "systick.h"
#include "sysclock.h"
#include <stm32f3xx.h>

void
systick_delay_us(uint16_t delay)
{
    // Reload with a 1us resolution
    SysTick->LOAD = sysclock_get_prescaller_base(1000000);

    // Clear current value
    SysTick->VAL = 0;

    // Enable SysTick and select internal clock source
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    for (uint16_t i = 0; i < delay; i++)
    {
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
            ;
    }

    SysTick->CTRL = 0;
}