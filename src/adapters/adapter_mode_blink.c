#include <devices/blink.h>
#include <linebot/mode.h>
#include <linebot/port.h>

static inline void
apply_mode_indicator(linebot_mode_t const mode);

void
linebot_port_mode_changed(linebot_mode_t const mode)
{
    apply_mode_indicator(mode);
}

static inline void
apply_mode_indicator(linebot_mode_t const mode)
{
    switch (mode)
    {
        case LINEBOT_MODE_DETECTED:
            device_blink_set_toggles(DEVICE_BLINK_1, 4);
            break;

        case LINEBOT_MODE_FOLLOWING:
        case LINEBOT_MODE_RECOVERING:
            device_blink_set_toggles(DEVICE_BLINK_1, 8);
            break;

        case LINEBOT_MODE_MANUAL:
        default:
            device_blink_set_toggles(DEVICE_BLINK_1, 2);
    }
}
