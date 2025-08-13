#include "shell.hpp"
#include "data_store.hpp"
#include <cstdint>
#include <etl/string.h>
#include <libopencm3/stm32/dma.h>

namespace hardware
{

shell&
shell::of(data_store& store, uint32_t dma_port, uint8_t dma_channel)
{
    static shell device{store, dma_port, dma_channel};
    return device;
}

char
shell::read()
{
    return store_.shell_command_;
}

void
shell::send(char* data, uint8_t length)
{
    if (length > store_.SHELL_TXBUFF_LENGTH)
    {
        length = store_.SHELL_TXBUFF_LENGTH;
    }

    for (uint8_t i = 0; i < length; ++i)
    {
        store_.shell_output_buffer_[i] = data[i];
    }

    dma_disable_channel(dma_port_, dma_channel_);
    dma_set_number_of_data(dma_port_, dma_channel_, length);
    dma_enable_channel(dma_port_, dma_channel_);
}

} // namespace hardware
