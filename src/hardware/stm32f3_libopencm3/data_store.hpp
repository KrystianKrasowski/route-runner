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
    const uint8_t p_dualshock2_request[DUALSHOCK2_BUFFER_LENGTH] = {
        0x1, 0x42, 0x0, 0x0, 0x0
    };

    volatile uint8_t  p_dualshock2_wbuff[DUALSHOCK2_BUFFER_LENGTH];
    volatile uint8_t  p_dualshock2_rbuff[DUALSHOCK2_BUFFER_LENGTH];
    volatile uint16_t p_qtrhd06a_wbuff[QTRHD06A_BUFFER_LENGTH];
    volatile uint16_t p_qtrhd06a_rbuff[QTRHD06A_BUFFER_LENGTH];
    volatile char     shell_command;
    volatile char     shell_output[SHELL_TXBUFF_LENGTH];

    void
    on_dualshock2_rx_isr();

    void
    on_qtrhd06a_conversion_isr();
};

} // namespace hardware
