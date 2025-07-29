#include "timeout.hpp"
#include <cstdint>
#include <libopencm3/stm32/timer.h>

namespace hardware
{

timeout&
timeout::of(uint32_t timer_port)
{
    static timeout device{timer_port};
    return device;
}

void
timeout::start(uint16_t millis)
{
    timer_set_period(timer_port_, millis);
    timer_set_counter(timer_port_, 0);
    timer_enable_counter(timer_port_);
}

void
timeout::stop()
{
    timer_disable_counter(timer_port_);
}

} // namespace hardware
