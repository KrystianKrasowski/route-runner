#include "systick.h"
#include <libopencm3/cm3/systick.h>
#include <stdint.h>

void
systick_delay_us(uint16_t delay)
{
    // TODO: Extract system clock value
    systick_set_frequency(1000000, 16000000);
    systick_clear();
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_counter_enable();

    for (uint16_t i = 0; i < delay; i++)
    {
        while ((systick_get_countflag()) == 0)
            ;
    }

    systick_counter_disable();
}
