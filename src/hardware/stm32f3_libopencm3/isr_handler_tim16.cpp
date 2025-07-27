#include "isr_handler_tim16.hpp"
#include "shell.hpp"
#include <libopencm3/stm32/timer.h>

namespace hardware
{

isr_handler_tim16&
isr_handler_tim16::of(shell& shell)
{
    static isr_handler_tim16 handler{shell};
    return handler;
}

void
isr_handler_tim16::handle()
{
    if (timer_get_flag(TIM16, TIM_SR_UIF))
    {
        timer_clear_flag(TIM16, TIM_SR_UIF);
        shell_.dump();
    }
}

} // namespace hardware
