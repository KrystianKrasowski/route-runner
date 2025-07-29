#include "isr_handler_tim15.hpp"
#include "device/isr_event_emitter.hpp"
#include <libopencm3/stm32/timer.h>

namespace hardware
{

isr_handler_tim15&
isr_handler_tim15::of(device::isr_event_emitter& events)
{
    static isr_handler_tim15 handler{events};
    return handler;
}

void
isr_handler_tim15::handle()
{
    if (timer_get_flag(TIM15, TIM_SR_UIF))
    {
        timer_clear_flag(TIM15, TIM_SR_UIF);
        // TODO: This causes one timer to one kind of timeout, may be not
        // efficient
        events_.emit(device::event_id::TIMEOUT);
    }
}

} // namespace hardware
