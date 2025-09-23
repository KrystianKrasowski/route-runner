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
        data_store* const p_store,
        uint32_t const    dma_port,
        uint8_t const     dma_channel
    );

    char
    read() const override;

    void
    send(char* data, uint8_t length) const override;

private:

    data_store* const p_store_;
    uint32_t const    dma_port_;
    uint8_t const     dma_channel_;
};

} // namespace hardware
