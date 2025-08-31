#include "isr_handler_tim15.hpp"
#include "device/isr_event_emitter.hpp"
#include <libopencm3/stm32/timer.h>

namespace hardware
{

void
isr_handler_tim15::handle()
{
    if (timer_get_flag(TIM15, TIM_SR_UIF))
    {
        timer_clear_flag(TIM15, TIM_SR_UIF);
        // TODO: This causes one timer to one kind of timeout, may be not
        // efficient

        emit_event(device::event_id::TIMEOUT);
    }
}

} // namespace hardware
