#pragma once

#include <cstdint>
#include <etl/array.h>

namespace hardware
{

struct data_store
{
    static const uint8_t dualshock2_buffer_length = 5;

    // I feel like this should be defined in dualshock2 class, but it is too
    // much of a hassle with copying C-like arrays just to make code clean.
    const uint8_t p_dualshock2_request[dualshock2_buffer_length] = {
        0x1, 0x42, 0x0, 0x0, 0x0
    };

    volatile uint8_t p_dualshock2_wbuff[dualshock2_buffer_length];

    volatile uint8_t p_dualshock2_rbuff[dualshock2_buffer_length];

    void
    on_dualshock2_rx_isr();
};

} // namespace hardware
