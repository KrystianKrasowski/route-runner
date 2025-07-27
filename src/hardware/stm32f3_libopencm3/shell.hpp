#pragma once

#include "data_store.hpp"
#include "device/shell.hpp"
#include <cstdint>
#include <etl/memory_model.h>
#include <etl/queue.h>
#include <etl/string.h>

namespace hardware
{

constexpr auto MEMORY_MODEL = etl::memory_model::MEMORY_MODEL_SMALL;

class shell : public device::shell
{
public:

    static shell&
    of(data_store& store, uint32_t dma_port, uint8_t dma_channel);

    char
    read() override;

    void
    send(etl::string<MAX_LENGTH>& message) override;

    void
    dump();

private:

    data_store&                                store_;
    uint32_t                                   dma_port_;
    uint8_t                                    dma_channel_;
    etl::queue<char, MAX_LENGTH, MEMORY_MODEL> output_chars_;

    shell(data_store& store, uint32_t dma_port, uint8_t dma_channel)
        : store_{store},
          dma_port_{dma_port},
          dma_channel_{dma_channel}
    {
        output_chars_.clear();
    }

    uint8_t dump_queue_to_dma_buffer();
};

} // namespace hardware
