#include "timeout.hpp"
#include <cstdint>
#include <libopencm3/stm32/timer.h>

namespace hardware
{

timeout::timeout(const uint32_t timer_port)
    : timer_port_{timer_port}
{
}

void
timeout::start(uint16_t millis) const
{
    timer_set_period(timer_port_, millis);
    timer_set_counter(timer_port_, 0);
    timer_enable_counter(timer_port_);
}

void
timeout::stop() const
{
    timer_disable_counter(timer_port_);
}

} // namespace hardware
