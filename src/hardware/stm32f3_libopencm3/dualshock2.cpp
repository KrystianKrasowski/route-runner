#include "device/dualshock2.hpp"
#include "data_store.hpp"
#include "dualshock2.hpp"
#include <cstdint>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>

namespace hardware
{

dualshock2::dualshock2(
    uint32_t const    chip_select_port,
    uint16_t const    chip_select_pin,
    uint32_t const    spi_dma_port,
    uint8_t const     spi_dma_tx_channel,
    uint8_t const     spi_dma_rx_channel,
    data_store* const p_store
)
    : p_store_{p_store},
      chip_select_port_{chip_select_port},
      spi_dma_port_{spi_dma_port},
      chip_select_pin_{chip_select_pin},
      spi_dma_tx_channel_{spi_dma_tx_channel},
      spi_dma_rx_channel_{spi_dma_rx_channel}
{
}

uint16_t
dualshock2::read() const
{
    uint16_t commands = device::dualshock2::NONE;

    if (is_state_valid())
    {
        uint8_t msb = p_store_->p_dualshock2_rbuff_[4];
        uint8_t lsb = p_store_->p_dualshock2_rbuff_[3];

        commands = ~(((uint16_t)msb << 8) | lsb);
    }

    return commands;
}

void
dualshock2::poll_start() const
{
    gpio_clear(chip_select_port_, chip_select_pin_);
    dma_set_number_of_data(
        spi_dma_port_, spi_dma_tx_channel_, data_store::DUALSHOCK2_BUFFER_LENGTH
    );
    dma_set_number_of_data(
        spi_dma_port_, spi_dma_rx_channel_, data_store::DUALSHOCK2_BUFFER_LENGTH
    );
    dma_set_memory_address(
        spi_dma_port_,
        spi_dma_rx_channel_,
        (uint32_t)p_store_->p_dualshock2_wbuff_
    );
    dma_enable_channel(spi_dma_port_, spi_dma_tx_channel_);
    dma_enable_channel(spi_dma_port_, spi_dma_rx_channel_);
}

void
dualshock2::poll_end() const
{
    dma_disable_channel(spi_dma_port_, spi_dma_tx_channel_);
    dma_disable_channel(spi_dma_port_, spi_dma_rx_channel_);
    gpio_set(chip_select_port_, chip_select_pin_);
}

bool
dualshock2::is_state_valid() const
{
    volatile uint8_t const * state_buffer = p_store_->p_dualshock2_rbuff_;

    bool b_1st_byte_valid = 0xff == state_buffer[0];
    bool b_2nd_byte_valid = 0x41 == state_buffer[1] || 0x73 == state_buffer[1];
    bool b_3rd_byte_valid = 0x5a == state_buffer[2];

    return b_1st_byte_valid && b_2nd_byte_valid && b_3rd_byte_valid;
}

} // namespace hardware
