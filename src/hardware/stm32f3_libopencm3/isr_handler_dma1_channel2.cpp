#include "isr_handler_dma1_channel2.hpp"
#include "dualshock2.hpp"
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/f3/dma.h>

namespace hardware
{

isr_handler_dma1_channel2::isr_handler_dma1_channel2(
    dualshock2& remote_control, data_store& data_store
)
    : remote_control_{remote_control},
      data_store_{data_store}
{
}

void
isr_handler_dma1_channel2::handle()
{
    if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL2, DMA_TCIF))
    {
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL2, DMA_TCIF);
        remote_control_.poll_end();
        data_store_.swap_dualshock2_buffers_isr();
        emit_event(device::event_id::DUALSHOCK2_RX_COMPLETE);
    }
}

} // namespace hardware
