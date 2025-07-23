#include "isr_handler_dma1_channel2.hpp"
#include "device/isr_event_emitter.hpp"
#include "dualshock2.hpp"
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/f3/dma.h>

namespace hardware
{

isr_handler_dma1_channel2&
isr_handler_dma1_channel2::of(
    dualshock2&                dualshock2,
    data_store&                data_store,
    device::isr_event_emitter& event_emitter
)
{
    static isr_handler_dma1_channel2 handler{
        dualshock2, data_store, event_emitter
    };

    return handler;
}

void
isr_handler_dma1_channel2::handle()
{
    if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL2, DMA_TCIF))
    {
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL2, DMA_TCIF);
        remote_control_.poll_end();
        data_store_.on_dualshock2_rx_isr();
        event_emitter_.emit(device::event_id::DUALSHOCK2_RX_COMPLETE);
    }
}

} // namespace hardware
