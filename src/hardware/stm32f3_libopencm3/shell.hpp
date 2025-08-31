#pragma once

#include "data_store.hpp"
#include "device/shell.hpp"
#include <cstdint>

namespace hardware
{

class shell : public device::shell
{
public:

    shell(
        data_store& store, const uint32_t dma_port, const uint8_t dma_channel
    );

    char
    read() override;

    void
    send(char* data, uint8_t length) override;

private:

    data_store&    store_;
    const uint32_t dma_port_;
    const uint8_t  dma_channel_;
};

} // namespace hardware
