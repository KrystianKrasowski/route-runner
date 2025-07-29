#include "isr_handler_usart2.hpp"
#include "data_store.hpp"
#include "device/isr_event_emitter.hpp"
#include <libopencm3/stm32/usart.h>

namespace hardware
{

isr_handler_usart2&
isr_handler_usart2::of(device::isr_event_emitter& events, data_store& store)
{
    static isr_handler_usart2 handler = isr_handler_usart2{events, store};
    return handler;
}

void
isr_handler_usart2::handle()
{
    if (usart_get_flag(USART2, USART_ISR_RXNE))
    {
        store_.shell_command = usart_recv(USART2);
        events_.emit(device::event_id::SHELL_COMMANDED);
    }
}

} // namespace hardware
