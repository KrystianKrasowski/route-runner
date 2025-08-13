#pragma once

#include "data_store.hpp"
#include "device/shell.hpp"
#include <cstdint>

namespace hardware
{

class shell : public device::shell
{
public:

    static shell&
    of(data_store& store, uint32_t dma_port, uint8_t dma_channel);

    char
    read() override;

    void
    send(char* data, uint8_t length) override;

private:

    data_store&                                store_;
    uint32_t                                   dma_port_;
    uint8_t                                    dma_channel_;

    shell(data_store& store, uint32_t dma_port, uint8_t dma_channel)
        : store_{store},
          dma_port_{dma_port},
          dma_channel_{dma_channel}
    {
    }
};

} // namespace hardware
