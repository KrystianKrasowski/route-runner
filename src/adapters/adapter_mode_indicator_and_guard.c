#include <adapters.h>
#include <linebot/port.h>
#include <tim1.h>
#include <tim15.h>

static inline void
indicate_tracking_mode(linebot_mode_t const mode);

static inline void
indicate_detected_mode(linebot_mode_t const mode);

static inline void
indicate_manual_mode(linebot_mode_t const mode);

static inline void
start_route_guard(linebot_mode_t const mode);

static inline void
stop_route_guard(linebot_mode_t const mode);

void
adapters_mode_init(void)
{
    tim1_ch1_init();
    tim1_ch1_set_toggles(2);
    tim15_init();
}

void
linebot_port_mode_changed(linebot_mode_t const value)
{
    indicate_tracking_mode(value);
    indicate_detected_mode(value);
    indicate_manual_mode(value);
    start_route_guard(value);
    stop_route_guard(value);
}

static inline void
indicate_tracking_mode(linebot_mode_t const mode)
{
    if (linebot_mode_is_tracking(mode))
    {
        tim1_ch1_set_toggles(8);
    }
}

static inline void
indicate_detected_mode(linebot_mode_t const mode)
{
    if (linebot_mode_is_detected(mode))
    {
        tim1_ch1_set_toggles(4);
    }
}

static inline void
indicate_manual_mode(linebot_mode_t const mode)
{
    if (linebot_mode_is_manual(mode))
    {
        tim1_ch1_set_toggles(2);
    }
}

static inline void
start_route_guard(linebot_mode_t const mode)
{
    if (linebot_mode_is_recovering(mode))
    {
        tim15_start();
    }
}

static inline void
stop_route_guard(linebot_mode_t const mode)
{
    if (!linebot_mode_is_recovering(mode))
    {
        tim15_stop();
    }
}