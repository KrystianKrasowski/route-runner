#include "isr_handler_tim2.hpp"
#include "dualshock2.hpp"
#include <libopencm3/stm32/timer.h>

namespace hardware
{

isr_handler_tim2&
isr_handler_tim2::of(dualshock2& dualshock2_)
{
    static isr_handler_tim2 handler{dualshock2_};
    return handler;
}

void
isr_handler_tim2::handle()
{
    if (timer_get_flag(TIM2, TIM_SR_UIF))
    {
        timer_clear_flag(TIM2, TIM_SR_UIF);
        dualshock_.poll_start();
    }
}

} // namespace hardware
