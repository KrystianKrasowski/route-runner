#pragma once

#include "data_store.hpp"
#include "device/dualshock2.hpp"
#include <cstdint>
#include <etl/array.h>

namespace hardware
{

class dualshock2 : public device::dualshock2
{
public:

    dualshock2(
        const uint32_t chip_select_port,
        const uint16_t chip_select_pin,
        const uint32_t spi_dma_port,
        const uint8_t  spi_dma_tx_channel,
        const uint8_t  spi_dma_rx_channel,
        data_store&    store
    );

    uint16_t
    read() override;

    void
    poll_start();

    void
    poll_end();

private:

    data_store&    store_;
    const uint32_t chip_select_port_;
    const uint32_t spi_dma_port_;
    const uint16_t chip_select_pin_;
    const uint8_t  spi_dma_tx_channel_;
    const uint8_t  spi_dma_rx_channel_;

    bool
    is_state_valid();
};

} // namespace hardware
