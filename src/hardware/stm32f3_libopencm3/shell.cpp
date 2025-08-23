#include "shell.hpp"
#include "data_store.hpp"
#include <cstdint>
#include <etl/string.h>
#include <libopencm3/stm32/dma.h>

namespace hardware
{

shell::shell(
    data_store& store, const uint32_t dma_port, const uint8_t dma_channel
)
    : store_{store},
      dma_port_{dma_port},
      dma_channel_{dma_channel}
{
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

    // This copies only 4 bytes. I could implement some callback, delegate, etc.
    // But it obfuscates code a lot. And with this implementation we have
    // separation of buffers
    for (uint8_t i = 0; i < length; ++i)
    {
        store_.shell_output_buffer_[i] = data[i];
    }

    dma_disable_channel(dma_port_, dma_channel_);
    dma_set_number_of_data(dma_port_, dma_channel_, length);
    dma_enable_channel(dma_port_, dma_channel_);
}

} // namespace hardware
