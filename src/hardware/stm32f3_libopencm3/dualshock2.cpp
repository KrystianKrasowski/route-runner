#include "device/dualshock2.hpp"
#include "data_store.hpp"
#include "dualshock2.hpp"
#include <cstdint>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/gpio.h>

namespace hardware
{

dualshock2&
dualshock2::of(
    uint32_t                chip_select_port,
    uint16_t                chip_select_pin,
    uint32_t                spi_dma_port,
    uint8_t                 spi_dma_tx_channel,
    uint8_t                 spi_dma_rx_channel,
    volatile uint8_t* const state_buffer
)
{
    static dualshock2 device{
        chip_select_port,
        chip_select_pin,
        spi_dma_port,
        spi_dma_tx_channel,
        spi_dma_rx_channel,
        state_buffer
    };

    return device;
}

uint16_t
dualshock2::read()
{
    uint16_t commands = device::dualshock2::NONE;

    if (is_state_valid())
    {
        uint8_t msb = state_buffer_[4];
        uint8_t lsb = state_buffer_[3];

        commands = ~(((uint16_t)msb << 8) | lsb);
    }

    return commands;
}

void
dualshock2::poll_start()
{
    gpio_clear(chip_select_port_, chip_select_pin_);
    dma_set_number_of_data(
        spi_dma_port_, spi_dma_tx_channel_, data_store::DUALSHOCK2_BUFFER_LENGTH
    );
    dma_set_number_of_data(
        spi_dma_port_, spi_dma_rx_channel_, data_store::DUALSHOCK2_BUFFER_LENGTH
    );
    dma_enable_channel(spi_dma_port_, spi_dma_tx_channel_);
    dma_enable_channel(spi_dma_port_, spi_dma_rx_channel_);
}

void
dualshock2::poll_end()
{
    dma_disable_channel(spi_dma_port_, spi_dma_tx_channel_);
    dma_disable_channel(spi_dma_port_, spi_dma_rx_channel_);
    gpio_set(chip_select_port_, chip_select_pin_);
}

bool
dualshock2::is_state_valid()
{
    bool b_1st_byte_valid = 0xff == state_buffer_[0];
    bool b_2nd_byte_valid =
        0x41 == state_buffer_[1] || 0x73 == state_buffer_[1];
    bool b_3rd_byte_valid = 0x5a == state_buffer_[2];

    return b_1st_byte_valid && b_2nd_byte_valid && b_3rd_byte_valid;
}

} // namespace hardware
