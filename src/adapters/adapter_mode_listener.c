#include <devices/blink.h>
#include <devices/timeout_guard.h>
#include <pathbot/api.h>
#include <pathbot/port.h>

static inline void
apply_mode_indicator(pathbot_mode_t const mode);

static inline void
apply_route_guard(pathbot_mode_t const mode);

void
pathbot_port_mode_changed(pathbot_mode_t const mode)
{
    apply_mode_indicator(mode);
    apply_route_guard(mode);
}

static inline void
apply_mode_indicator(pathbot_mode_t const mode)
{
    switch (mode)
    {
        case PATHBOT_MODE_DETECTED:
            device_blink_set_sequence(DEVICE_BLINK_1, 0x5);
            break;

        case PATHBOT_MODE_FOLLOWING:
        case PATHBOT_MODE_RECOVERING:
            device_blink_set_sequence(DEVICE_BLINK_1, 0x55);
            break;

        case PATHBOT_MODE_MANUAL:
        default:
            device_blink_set_sequence(DEVICE_BLINK_1, 0x1);
    }
}

static inline void
apply_route_guard(pathbot_mode_t const mode)
{
    if (pathbot_mode_is_recovering(mode))
    {
        device_timeout_guard_start(DEVICE_TIMEOUT_GUARD_ROUTE);
    }
    else
    {
        device_timeout_guard_stop(DEVICE_TIMEOUT_GUARD_ROUTE);
    }
}
