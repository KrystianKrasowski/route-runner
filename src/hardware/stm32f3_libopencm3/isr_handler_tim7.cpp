#include "isr_handler_tim7.hpp"
#include "toggle_sequence_gpio.hpp"
#include <libopencm3/stm32/timer.h>

namespace hardware
{

isr_handler_tim7&
isr_handler_tim7::of(toggle_sequence_gpio& toggle_sequence)
{
    static isr_handler_tim7 handler{toggle_sequence};
    return handler;
}

void
isr_handler_tim7::handle()
{
    if (timer_get_flag(TIM7, TIM_SR_UIF))
    {
        timer_clear_flag(TIM7, TIM_SR_UIF);
        toggle_sequence.toggle();
    }
}

} // namespace hardware
