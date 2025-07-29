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
    return store_.shell_command;
}

void
shell::send(etl::string<MAX_LENGTH>& message)
{
    if (output_chars_.available() >= message.size())
    {
        for (auto& chr : message)
        {
            output_chars_.push(chr);
        }
    }
}

void
shell::dump()
{
    if (!output_chars_.empty())
    {
        store_.clear_shell_output();

        uint8_t data_length = dump_queue_to_dma_buffer();

        dma_disable_channel(dma_port_, dma_channel_);
        dma_set_number_of_data(dma_port_, dma_channel_, data_length);
        dma_enable_channel(dma_port_, dma_channel_);
    }
}

uint8_t
shell::dump_queue_to_dma_buffer()
{
    uint8_t char_index = 0;

    while (!output_chars_.empty())
    {
        // not poped into buffer directly, due to volatile
        char chr;
        output_chars_.pop_into(chr);
        store_.p_shell_output[char_index] = chr;
        char_index++;
    }

    return char_index;
}

} // namespace hardware
