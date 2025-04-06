#include <core.h>
#include <tim1.h>

void
core_port_mode_indicator_init(void)
{
    tim1_ch1_init();
    tim1_ch1_set_toggles(2);
}

void
core_port_mode_indicator_apply(core_mode_value_t value)
{
    switch (value)
    {
        case CORE_MODE_FOLLOWING:
            tim1_ch1_set_toggles(8);
            break;
        case CORE_MODE_DETECTED:
            tim1_ch1_set_toggles(4);
            break;
        case CORE_MODE_MANUAL:
        default:
            tim1_ch1_set_toggles(2);
    }
}