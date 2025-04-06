#include <core.h>
#include <tim15.h>
#include <tim1.h>

static inline void
indicate_tracking_mode(core_mode_t *mode);

static inline void
indicate_detected_mode(core_mode_t *mode);

static inline void
indicate_manual_mode(core_mode_t *mode);

static inline void
start_route_guard(core_mode_t *mode);

static inline void
stop_route_guard(core_mode_t *mode);

void
core_port_mode_init(void)
{
    tim1_ch1_init();
    tim1_ch1_set_toggles(2);
    tim15_init();
}

void
core_port_mode_changed(core_mode_t *mode)
{
    indicate_tracking_mode(mode);
    indicate_detected_mode(mode);
    indicate_manual_mode(mode);
    start_route_guard(mode);
    stop_route_guard(mode);
}

static inline void
indicate_tracking_mode(core_mode_t *mode)
{
    if (core_mode_is_tracking(mode))
    {
        tim1_ch1_set_toggles(8);
    }
}

static inline void
indicate_detected_mode(core_mode_t *mode)
{
    if (core_mode_is_detected(mode))
    {
        tim1_ch1_set_toggles(4);
    }
}

static inline void
indicate_manual_mode(core_mode_t *mode)
{
    if (core_mode_is_manual(mode))
    {
        tim1_ch1_set_toggles(2);
    }
}

static inline void
start_route_guard(core_mode_t *mode)
{
    if (core_mode_is_recovering(mode))
    {
        tim15_start();
    }
}

static inline void
stop_route_guard(core_mode_t *mode)
{
    if(core_mode_is_following(mode) || !core_mode_is_tracking(mode))
    {
        tim15_stop();
    }
}