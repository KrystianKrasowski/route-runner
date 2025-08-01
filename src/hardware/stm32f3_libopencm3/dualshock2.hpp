#pragma once

#include "device/dualshock2.hpp"
#include <cstdint>
#include <etl/array.h>

namespace hardware
{

class dualshock2 : public device::dualshock2
{
public:

    static dualshock2&
    of(uint32_t                 chip_select_port,
       uint16_t                 chip_select_pin,
       uint32_t                 spi_dma_port,
       uint8_t                  spi_dma_tx_channel,
       uint8_t                  spi_dma_rx_channel,
       volatile uint8_t * const state_buffer);

    uint16_t
    read() override;

    void
    poll_start();

    void
    poll_end();

private:

    uint32_t                 chip_select_port_;
    uint16_t                 chip_select_pin_;
    uint32_t                 spi_dma_port_;
    uint8_t                  spi_dma_tx_channel_;
    uint8_t                  spi_dma_rx_channel_;
    volatile uint8_t * const state_buffer_;

    dualshock2(
        uint32_t                 chip_select_port,
        uint16_t                 chip_select_pin,
        uint32_t                 spi_dma_port,
        uint8_t                  spi_dma_tx_channel,
        uint8_t                  spi_dma_rx_channel,
        volatile uint8_t * const state_buffer
    )
        : chip_select_port_{chip_select_port},
          chip_select_pin_{chip_select_pin},
          spi_dma_port_{spi_dma_port},
          spi_dma_tx_channel_{spi_dma_tx_channel},
          spi_dma_rx_channel_{spi_dma_rx_channel},
          state_buffer_{state_buffer}
    {
    }

    bool
    is_state_valid();
};

} // namespace hardware
