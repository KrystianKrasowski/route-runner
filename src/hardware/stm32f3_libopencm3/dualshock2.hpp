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
        uint32_t const    chip_select_port,
        uint16_t const    chip_select_pin,
        uint32_t const    spi_dma_port,
        uint8_t const     spi_dma_tx_channel,
        uint8_t const     spi_dma_rx_channel,
        data_store* const store
    );

    uint16_t
    read() const override;

    void
    poll_start() const;

    void
    poll_end() const;

private:

    data_store* const p_store_;
    uint32_t const    chip_select_port_;
    uint32_t const    spi_dma_port_;
    uint16_t const    chip_select_pin_;
    uint8_t const     spi_dma_tx_channel_;
    uint8_t const     spi_dma_rx_channel_;

    bool
    is_state_valid() const;
};

} // namespace hardware
