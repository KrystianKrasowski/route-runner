#include "isr_handler_tim7.hpp"
#include "toggle_sequence_gpio.hpp"
#include <libopencm3/stm32/timer.h>

namespace hardware
{

isr_handler_tim7::isr_handler_tim7(toggle_sequence_gpio& toggle_sequence)
    : toggle_sequence_{toggle_sequence}
{
}

void
isr_handler_tim7::handle()
{
    if (timer_get_flag(TIM7, TIM_SR_UIF))
    {
        timer_clear_flag(TIM7, TIM_SR_UIF);
        toggle_sequence_.toggle();
    }
}

} // namespace hardware
