#include "isr_handler_dma1_channel1.hpp"
#include "data_store.hpp"
#include "device/isr_event_emitter.hpp"
#include "qtrhd06a.hpp"
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/f3/dma.h>

namespace hardware
{

isr_handler_dma1_channel1::isr_handler_dma1_channel1(
    qtrhd06a& line_sensor, data_store& data_store
)
    : line_sensor_{line_sensor},
      data_store_{data_store}
{
}

void
isr_handler_dma1_channel1::handle()
{
    if (dma_get_interrupt_flag(DMA1, DMA_CHANNEL1, DMA_TCIF))
    {
        dma_clear_interrupt_flags(DMA1, DMA_CHANNEL1, DMA_TCIF);
        data_store_.swap_qtrhd06a_buffers_isr();

        uint32_t memory_address = (uint32_t)data_store_.p_qtrhd06a_wbuff_;
        dma_disable_channel(DMA1, DMA_CHANNEL1);
        dma_set_memory_address(DMA1, DMA_CHANNEL1, memory_address);
        dma_enable_channel(DMA1, DMA_CHANNEL1);
        emit_event(device::event_id::QTRHD06A_CONVERSION_COMPLETE);
    }
}

} // namespace hardware
