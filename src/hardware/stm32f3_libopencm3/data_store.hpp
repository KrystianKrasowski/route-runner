#pragma once

#include <cstdint>
#include <device/shell.hpp>

namespace hardware
{

struct data_store
{
    static constexpr uint8_t DUALSHOCK2_BUFFER_LENGTH = 5;
    static constexpr uint8_t QTRHD06A_BUFFER_LENGTH   = 40;
    static constexpr uint8_t SHELL_TXBUFF_LENGTH = device::shell::MAX_LENGTH;
    static constexpr uint8_t DUALSHOCK2_REQUEST[DUALSHOCK2_BUFFER_LENGTH] = {
        0x1, 0x42, 0x0, 0x0, 0x0
    };

    volatile uint8_t*  p_dualshock2_wbuff_ = nullptr;
    volatile uint8_t*  p_dualshock2_rbuff_ = nullptr;
    volatile uint16_t* p_qtrhd06a_wbuff_   = nullptr;
    volatile uint16_t* p_qtrhd06a_rbuff_   = nullptr;

    volatile uint16_t qtrhd06a_buffer1_[QTRHD06A_BUFFER_LENGTH];
    volatile uint16_t qtrhd06a_buffer2_[QTRHD06A_BUFFER_LENGTH];
    volatile uint8_t  dualshock2_buffer1_[DUALSHOCK2_BUFFER_LENGTH];
    volatile uint8_t  dualshock2_buffer2_[DUALSHOCK2_BUFFER_LENGTH];
    volatile char     shell_command_;
    volatile char     shell_output_buffer_[SHELL_TXBUFF_LENGTH];

    data_store()
        : p_dualshock2_wbuff_{dualshock2_buffer1_},
          p_dualshock2_rbuff_{dualshock2_buffer2_},
          p_qtrhd06a_wbuff_{qtrhd06a_buffer1_},
          p_qtrhd06a_rbuff_{qtrhd06a_buffer2_}
    {
    }

    void
    swap_dualshock2_buffers_isr();

    void
    swap_qtrhd06a_buffers_isr();
};

} // namespace hardware
