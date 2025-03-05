#include <core.h>
#include <tim1.h>

void
core_port_state_indicator_init(void)
{
    tim1_ch1_init();
    tim1_ch1_set_toggles(2);
}

void
core_port_state_indicator_apply(core_vehicle_state_t state)
{
    switch (state)
    {
        case CORE_VEHICLE_STATE_LINE_DETECTED:
            tim1_ch1_set_toggles(4);
            break;
        case CORE_VEHICLE_STATE_MANUAL:
        default:
            tim1_ch1_set_toggles(2);
    }
}