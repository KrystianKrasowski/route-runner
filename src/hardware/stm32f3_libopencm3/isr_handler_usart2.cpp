#include "isr_handler_usart2.hpp"
#include "data_store.hpp"
#include "device/isr_event_emitter.hpp"
#include <libopencm3/stm32/usart.h>

namespace hardware
{

isr_handler_usart2::isr_handler_usart2(data_store& store)
    : store_{store}
{
}

void
isr_handler_usart2::handle()
{
    if (usart_get_flag(USART2, USART_ISR_RXNE))
    {
        store_.shell_command_ = usart_recv(USART2);
        emit_event(device::event_id::SHELL_COMMANDED);
    }
}

} // namespace hardware
