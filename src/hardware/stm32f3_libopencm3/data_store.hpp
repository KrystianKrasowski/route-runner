#pragma once

#include <cstdint>
#include <etl/array.h>

namespace hardware
{

struct data_store
{
    static const uint8_t DUALSHOCK2_BUFFER_LENGTH = 5;
    static const uint8_t QTRHD06A_BUFFER_LENGTH   = 40;
    static const uint8_t SHELL_TXBUFF_LENGTH      = 100;

    // I feel like this should be defined in dualshock2 class, but it is too
    // much of a hassle with copying C-like arrays just to make code clean.
    // Moreover, DOD decouples data from object, so maybe this is actually
    // good approach?
    const uint8_t p_dualshock2_request_[DUALSHOCK2_BUFFER_LENGTH] = {
        0x1, 0x42, 0x0, 0x0, 0x0
    };

    volatile uint8_t  p_dualshock2_wbuff_[DUALSHOCK2_BUFFER_LENGTH];
    volatile uint8_t  p_dualshock2_rbuff_[DUALSHOCK2_BUFFER_LENGTH];
    volatile uint16_t p_qtrhd06a_wbuff_[QTRHD06A_BUFFER_LENGTH];
    volatile uint16_t p_qtrhd06a_rbuff_[QTRHD06A_BUFFER_LENGTH];
    volatile char     shell_command_;
    volatile char     p_shell_output_[SHELL_TXBUFF_LENGTH];

    void
    on_dualshock2_rx_isr();

    void
    on_qtrhd06a_conversion_isr();

    void
    clear_shell_output();
};

} // namespace hardware
