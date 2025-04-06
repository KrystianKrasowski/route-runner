#include <core.h>
#include <tim1.h>

void
core_port_mode_init(void)
{
    tim1_ch1_init();
    tim1_ch1_set_toggles(2);
}

void
core_port_mode_changed(core_mode_t *mode)
{
    if (core_mode_is_tracking(mode))
    {
        tim1_ch1_set_toggles(8);
    }
    else if (core_mode_is_detected(mode))
    {
        tim1_ch1_set_toggles(4);
    }
    else
    {
        tim1_ch1_set_toggles(2);
    }
}